/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** triangle
*/

#include "triangle.hpp"

static Boxes make_triangle_bbox(const point3& v0, const point3& v1, const point3& v2)
{
    double x_min = fmin(v0.x(), fmin(v1.x(), v2.x()));
    double y_min = fmin(v0.y(), fmin(v1.y(), v2.y()));
    double z_min = fmin(v0.z(), fmin(v1.z(), v2.z()));
    double x_max = fmax(v0.x(), fmax(v1.x(), v2.x()));
    double y_max = fmax(v0.y(), fmax(v1.y(), v2.y()));
    double z_max = fmax(v0.z(), fmax(v1.z(), v2.z()));
    constexpr double pad = 1e-4;
    if (x_max - x_min < pad) { x_min -= pad; x_max += pad; }
    if (y_max - y_min < pad) { y_min -= pad; y_max += pad; }
    if (z_max - z_min < pad) { z_min -= pad; z_max += pad; }
    return Boxes(point3(x_min, y_min, z_min), point3(x_max, y_max, z_max));
}

triangle::triangle(const point3& v0, const point3& v1, const point3& v2, std::shared_ptr<material> mat) : vertex0(v0), vertex1(v1), vertex2(v2), mat(mat)
{
    bbox = make_triangle_bbox(v0, v1, v2);
    precomputed_normal = calculate_normal(v0, v1, v2);
}
 
triangle::triangle(const point3& v0, const point3& v1, const point3& v2, const vec3& uv0_, const vec3& uv1_, const vec3& uv2_, std::shared_ptr<material> mat) : vertex0(v0), vertex1(v1), vertex2(v2), uv0(uv0_), uv1(uv1_), uv2(uv2_), has_uvs(true), mat(mat)
{
    bbox = make_triangle_bbox(v0, v1, v2);
    precomputed_normal = calculate_normal(v0, v1, v2);
}
 
triangle::triangle(const point3& v0, const point3& v1, const point3& v2,
                   const vec3& uv0_, const vec3& uv1_, const vec3& uv2_,
                   const vec3& n0,   const vec3& n1,   const vec3& n2,
                   std::shared_ptr<material> mat)
    : vertex0(v0), vertex1(v1), vertex2(v2)
    , uv0(uv0_), uv1(uv1_), uv2(uv2_)
    , vn0(n0),  vn1(n1),  vn2(n2)
    , has_uvs(true), has_vnorms(true)
    , mat(mat)
{
    bbox = make_triangle_bbox(v0, v1, v2);
    precomputed_normal = calculate_normal(v0, v1, v2);
}

bool triangle::hit(const ray& r, interval ray_t, hit_record& rec) const
{
    vec3 edge1 = vertex1 - vertex0;
    vec3 edge2 = vertex2 - vertex0;
    vec3 h = r.direction().cross(edge2);
    double a = edge1.dot(h);
 
    if (fabs(a) < 1e-8)
        return false;
 
    double f = 1.0 / a;
    vec3   s = r.origin() - vertex0;
    double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return false;
 
    vec3   q = s.cross(edge1);
    double v = f * r.direction().dot(q);
    if (v < 0.0 || u + v > 1.0)
        return false;
 
    double t = f * edge2.dot(q);
    if (!ray_t.surrounds(t))
        return false;
 
    rec.t   = t;
    rec.p   = r.at(t);
    rec.mat = mat.get();
 
    if (has_vnorms) {
        double w = 1.0 - u - v;
        vec3 interpolated = w * vn0 + u * vn1 + v * vn2;
        double len = interpolated.length();
        vec3 smooth_normal = (len > 1e-12)
            ? interpolated / len
            : precomputed_normal;
        rec.set_face_normal(r, smooth_normal);
    } else {
        rec.set_face_normal(r, precomputed_normal);
    }
 
    if (has_uvs) {
        double w = 1.0 - u - v;
        rec.u = w * uv0.x() + u * uv1.x() + v * uv2.x();
        rec.v = w * uv0.y() + u * uv1.y() + v * uv2.y();
    } else {
        rec.u = u;
        rec.v = v;
    }
 
    return true;
}
 
Boxes triangle::bounding_box() const { return bbox; }
 
vec3 triangle::calculate_normal(const point3& v0, const point3& v1, const point3& v2)
{
    return Vec3Utils::unit_vector((v1 - v0).cross(v2 - v0));
}
