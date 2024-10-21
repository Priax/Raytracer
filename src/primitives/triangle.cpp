/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** triangle
*/

#include "triangle.hpp"

triangle::triangle(const point3& v0, const point3& v1, const point3& v2, std::shared_ptr<material> mat)
    : vertex0(v0), vertex1(v1), vertex2(v2), mat(mat) {

    double x_min = fmin(v0.x(), fmin(v1.x(), v2.x()));
    double y_min = fmin(v0.y(), fmin(v1.y(), v2.y()));
    double z_min = fmin(v0.z(), fmin(v1.z(), v2.z()));

    double x_max = fmax(v0.x(), fmax(v1.x(), v2.x()));
    double y_max = fmax(v0.y(), fmax(v1.y(), v2.y()));
    double z_max = fmax(v0.z(), fmax(v1.z(), v2.z()));

    bbox = Boxes(point3(x_min, y_min, z_min), point3(x_max, y_max, z_max));
}

bool triangle::hit(const ray& r, interval ray_t, hit_record& rec) const {
    vec3 edge1 = vertex1 - vertex0;
    vec3 edge2 = vertex2 - vertex0;
    vec3 h = r.direction().cross(edge2);
    double a = edge1.dot(h);

    if (fabs(a) < 1e-8)
        return false;

    double f = 1.0 / a;
    vec3 s = r.origin() - vertex0;
    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
        return false;

    vec3 q = s.cross(edge1);
    double v = f * r.direction().dot(q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    double t = f * edge2.dot(q);
    if (!ray_t.surrounds(t))
        return false;

    rec.t = t;
    rec.p = r.at(t);
    rec.set_face_normal(r, calculate_normal(vertex0, vertex1, vertex2));
    rec.mat = mat;

    return true;
}

Boxes triangle::bounding_box() const {
    return bbox;
}

vec3 triangle::calculate_normal(const point3& v0, const point3& v1, const point3& v2) {
    return Vec3Utils::unit_vector((v1 - v0).cross(v2 - v0));
}
