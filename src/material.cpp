#include "material.hpp"

color material::emitted(const ray& r_in, const hit_record& rec, double u, double v, const point3& p) const {
    (void)u;
    (void)v;
    (void)p;
    (void)r_in;
    (void)rec;
    return color(0, 0, 0);
}

bool material::scatter(const ray& r_in, const hit_record& rec, scatter_record& srec) const {
    (void)r_in;
    (void)rec;
    (void)srec;
    return false;
}

double material::scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const {
    (void)r_in;
    (void)rec;
    (void)scattered;
    return 0;
}

lambertian::lambertian(const color& albedo) : tex(std::make_shared<solid_color>(albedo)) {}
lambertian::lambertian(std::shared_ptr<texture> tex) : tex(tex) {}

bool lambertian::scatter(const ray& r_in, const hit_record& rec, scatter_record& srec) const {
    (void)r_in;
    srec.attenuation = tex->value(rec.u, rec.v, rec.p);
    srec.pdf_ptr = std::make_shared<cosine_pdf>(rec.normal);
    srec.skip_pdf = false;
    return true;
}

double lambertian::scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const {
    (void)r_in;
    double cos_theta = rec.normal.dot(Vec3Utils::unit_vector(scattered.direction()));
    return cos_theta < 0 ? 0 : cos_theta / pi;
}

metal::metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

bool metal::scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const {
    vec3 reflected = Vec3Utils::reflect(r_in.direction(), rec.normal);
    reflected = Vec3Utils::unit_vector(reflected) + (fuzz * Vec3Utils::random_unit_vector());

    srec.attenuation = albedo;
    srec.pdf_ptr = nullptr;
    srec.skip_pdf = true;
    srec.skip_pdf_ray = ray(rec.p, reflected, r_in.time());

    return true;
}

dielectric::dielectric(double refraction_index) : refraction_index(refraction_index) {}

bool dielectric::scatter(const ray &r_in, const hit_record &rec, scatter_record &srec) const {
    srec.attenuation = color(1.0, 1.0, 1.0);
    srec.pdf_ptr = nullptr;
    srec.skip_pdf = true;
    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

    vec3 unit_direction = Vec3Utils::unit_vector(r_in.direction());
    double cos_theta = fmin((-unit_direction).dot(rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    vec3 direction;

    if (cannot_refract || reflectance(cos_theta, ri) > Random::random_double())
        direction = Vec3Utils::reflect(unit_direction, rec.normal);
    else
        direction = Vec3Utils::refract(unit_direction, rec.normal, ri);

    srec.skip_pdf_ray = ray(rec.p, direction, r_in.time());
    return true;
}

double dielectric::reflectance(double cosine, double refraction_index) {
    double r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1-r0) * pow((1 - cosine), 5);
}

// Diffuse light Constructors
diffuse_light::diffuse_light(std::shared_ptr<texture> tex) : tex(tex) {}
diffuse_light::diffuse_light(const color& emit) : tex(std::make_shared<solid_color>(emit)) {}

color diffuse_light::emitted(const ray& r_in, const hit_record& rec, double u, double v, const point3& p) const {
    (void)r_in;
    if (!rec.front_face)
        return color(0,0,0);
    return tex->value(u, v, p);
}
