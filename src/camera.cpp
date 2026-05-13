/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** camera
*/

#include "camera.hpp"
#include "utility.hpp"
#include <vector>
#include <atomic>

void camera::render(const hittable& world, const hittable &lights) {
    initialize();

    std::vector<color> buffer(image_height * image_width);
    std::vector<bool> row_ready(image_height, false);
    std::atomic<int> rows_done(0);
    int next_row_to_push = 0;

    std::clog << "Rendering " << image_width << "x" << image_height
              << " spp=" << sqrt_spp * sqrt_spp << " depth=" << max_depth << "\n" << std::flush;
    #pragma omp parallel for schedule(dynamic, 1)
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);
            for (int s_j = 0; s_j < sqrt_spp; s_j++) {
                for (int s_i = 0; s_i < sqrt_spp; s_i++) {
                    ray r = get_ray(i, j, s_i, s_j);
                    color sample_color = ray_color(r, max_depth, world, lights);

                    double max_energy = 10.0;
                    if (sample_color.x() > max_energy || std::isnan(sample_color.x())) sample_color.e[0] = max_energy;
                    if (sample_color.y() > max_energy || std::isnan(sample_color.y())) sample_color.e[1] = max_energy;
                    if (sample_color.z() > max_energy || std::isnan(sample_color.z())) sample_color.e[2] = max_energy;

                    pixel_color += sample_color;
                }
            }
            buffer[j * image_width + i] = pixel_samples_scale * pixel_color;
        }
        {
            std::lock_guard<std::mutex> lock(*_colorsQueueMutex);
            row_ready[j] = true;
            while (next_row_to_push < image_height && row_ready[next_row_to_push]) {
                if (_colorsQueue != nullptr) {
                    for (int i = 0; i < image_width; i++) {
                        const color& c = buffer[next_row_to_push * image_width + i];
                        auto r = c.x(); if (r != r) r = 0.0;
                        auto g = c.y(); if (g != g) g = 0.0;
                        auto b = c.z(); if (b != b) b = 0.0;
                        r = std::sqrt(std::max(0.0, std::min(r, 0.999)));
                        g = std::sqrt(std::max(0.0, std::min(g, 0.999)));
                        b = std::sqrt(std::max(0.0, std::min(b, 0.999)));
                        _colorsQueue->push_back(sf::Color(int(256 * r), int(256 * g), int(256 * b)));
                    }
                }
                next_row_to_push++;
            }
        }
        int done = ++rows_done;
        std::clog << "\rRendering... " << (done * 100 / image_height) << "%" << std::flush;
    }

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (const auto& c : buffer)
        color::write_color(std::cout, c, nullptr, nullptr);

    std::clog << "\r\033[32mDone.\033[0m                          \n";
}

void camera::initialize()
{
    sqrt_spp = int(sqrt(samples_per_pixel));
    pixel_samples_scale = 1.0 / (sqrt_spp * sqrt_spp);
    recip_sqrt_spp = 1.0 / sqrt_spp;

    center = lookfrom;
    double theta = Random::degrees_to_radians(vfov);
    double h = tan(theta / 2);
    double viewport_height = 2 * h * focus_dist;
    double viewport_width = viewport_height * (double(image_width) / image_height);

    w = Vec3Utils::unit_vector(lookfrom - lookat);
    u = Vec3Utils::unit_vector(vup.cross(w));
    v = w.cross(u);

    vec3 viewport_u = viewport_width * u;
    vec3 viewport_v = viewport_height * -v;

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;
    point3 viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    double defocus_radius = focus_dist * tan(Random::degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

ray camera::get_ray(int i, int j, int s_i, int s_j) const {
    vec3 offset = sample_square_stratified(s_i, s_j);
    point3 pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

    point3 ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    point3 ray_direction = pixel_sample - ray_origin;
    double ray_time = Random::random_double();

    return ray(ray_origin, ray_direction, ray_time);
}

vec3 camera::sample_square_stratified(int s_i, int s_j) const {
    double px = ((s_i + Random::random_double()) * recip_sqrt_spp) - 0.5;
    double py = ((s_j + Random::random_double()) * recip_sqrt_spp) - 0.5;

    return vec3(px, py, 0);
}

vec3 camera::sample_square() const {
    return vec3(Random::random_double() - 0.5, Random::random_double() - 0.5, 0);
}

point3 camera::defocus_disk_sample() const {
    vec3 p = Vec3Utils::random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

color camera::ray_color(const ray &r, int depth, const hittable &world, const hittable &lights) const {
    if (depth <= 0)
        return color(0, 0, 0);

    hit_record rec;

    if (!world.hit(r, interval(0.001, infinity), rec))
        return background;

    scatter_record srec;
    color color_from_emission = rec.mat->emitted(r, rec, rec.u, rec.v, rec.p);

    if (!rec.mat->scatter(r, rec, srec))
        return color_from_emission;

    if (srec.skip_pdf) {
        return srec.attenuation * ray_color(srec.skip_pdf_ray, depth - 1, world, lights);
    }

    auto light_ptr = std::make_shared<hittable_pdf>(lights, rec.p); // directional light
    mixture_pdf p(light_ptr, srec.pdf_ptr);

    ray scattered = ray(rec.p, p.generate(), r.time());
    double pdf_val = p.value(scattered.direction());

    double scattering_pdf = rec.mat->scattering_pdf(r, rec, scattered);

    color sample_color = ray_color(scattered, depth - 1, world, lights);
    color color_from_scatter = (srec.attenuation * scattering_pdf * sample_color) / pdf_val;

    return (color_from_emission + color_from_scatter) * ambient_multiplier;
}
