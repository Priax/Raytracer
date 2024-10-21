/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** ortho
*/

#include "ortho.hpp"

// Orthonormal Frame Constructor
OrthonormalFrame::OrthonormalFrame() {};

vec3 OrthonormalFrame::u() const { return axis[0]; }
vec3 OrthonormalFrame::v() const { return axis[1]; }
vec3 OrthonormalFrame::w() const { return axis[2]; }

vec3 OrthonormalFrame::local(double a, double b, double c) const {
    return a * u() + b * v() + c * w();
}

vec3 OrthonormalFrame::local(const vec3& a) const {
    return a.x() * u() + a.y() * v() + a.z() * w();
}

void OrthonormalFrame::build_from_w(const vec3& w) {
    vec3 unit_w = Vec3Utils::unit_vector(w);
    vec3 a = (fabs(unit_w.x()) > 0.9) ? vec3(0,1,0) : vec3(1,0,0);
    vec3 v = Vec3Utils::unit_vector(unit_w.cross(a));
    vec3 u = unit_w.cross(v);
    axis[0] = u;
    axis[1] = v;
    axis[2] = unit_w;
}
