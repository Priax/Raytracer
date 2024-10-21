/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** pdf
*/
#include "pdf.hpp"

// Cosine Probability Density Function Constructor
cosine_pdf::cosine_pdf(const vec3& w) { uvw.build_from_w(w); }

double cosine_pdf::value(const vec3& direction) const {
    double cosine_theta = Vec3Utils::unit_vector(direction).dot(uvw.w());
    return fmax(0, cosine_theta / pi);
}

vec3 cosine_pdf::generate() const {
    return uvw.local(Vec3Utils::random_cosine_direction());
}

// Hittable Probability Density Function Constructor
hittable_pdf::hittable_pdf(const hittable& objects, const point3& origin) : objects(objects), origin(origin) {}

double hittable_pdf::value(const vec3& direction) const {
    return objects.pdf_value(origin, direction);
}

vec3 hittable_pdf::generate() const {
    return objects.random(origin);
}

// Mixture Probability Density Function Constructor
mixture_pdf::mixture_pdf(std::shared_ptr<pdf> p0, std::shared_ptr<pdf> p1) {
    p[0] = p0;
    p[1] = p1;
}

double mixture_pdf::value(const vec3& direction) const {
    return 0.5 * p[0]->value(direction) + 0.5 *p[1]->value(direction);
}

vec3 mixture_pdf::generate() const {
    if (Random::random_double() < 0.5)
        return p[0]->generate();
    else
        return p[1]->generate();
}
