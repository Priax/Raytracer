/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** camera
*/

#include "camera.hpp"
#include "utility.hpp"

// #pragma omp paralel for
void camera::render(const hittable& world, const hittable &lights) {
    initialize();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    int total_lines = image_height * image_width;
    int lines_rendered = 0;
    int percentage = 0;
    const int progress_width = 50;

    for (int j = 0; j < image_height; j++) {
        std::clog << "\r[\033[32m";
        int progress = (j * image_width) * progress_width / total_lines;
        for (int i = 0; i < progress_width; ++i) {
            if (i < progress) std::clog << "=";
            else std::clog << " ";
        }
        std::clog << "\033[0m] " << percentage << "% " << std::flush;

        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);
            //? Anti aliasing
            for (int s_j = 0; s_j < sqrt_spp; s_j++) {
                for (int s_i = 0; s_i < sqrt_spp; s_i++) {
                    ray r = get_ray(i, j, s_i, s_j);
                    pixel_color += ray_color(r, max_depth, world, lights);
                }
            }
            color::write_color(std::cout, pixel_samples_scale * pixel_color, _colorsQueue, _colorsQueueMutex);
            ++lines_rendered;
            percentage = (lines_rendered * 100) / total_lines;
        }
    }

    std::clog << "\r[\033[32m";
    for (int i = 0; i < progress_width; ++i) std::clog << "=";
    std::clog << "\033[0m] \033[32m100% Done.\033[0m                 \n";
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
