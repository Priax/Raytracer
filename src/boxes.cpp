/*
** EPITECH PROJECT, 2024
** rebelotte
** File description:
** boxes
*/

#include "boxes.hpp"

// Constructors
Boxes::Boxes() : x(), y(), z() {}
Boxes::Boxes(const interval& x, const interval& y, const interval& z) : x(x), y(y), z(z) {
    pad_to_minimums();
}

Boxes::Boxes(const point3& a, const point3& b) {
    x = (a[0] <= b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
    y = (a[1] <= b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
    z = (a[2] <= b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);
}

Boxes::Boxes(const Boxes& box0, const Boxes& box1) {
    x = interval(box0.x, box1.x);
    y = interval(box0.y, box1.y);
    z = interval(box0.z, box1.z);

    pad_to_minimums();
}

const interval& Boxes::axis_interval(int n) const {
    if (n == 1) return y;
    if (n == 2) return z;
    return x;
}

bool Boxes::hit(const ray& r, interval ray_t) const {
    const point3& ray_orig = r.origin();
    const vec3&   ray_dir  = r.direction();

    for (int axis = 0; axis < 3; axis++) {
        const interval& ax = axis_interval(axis);
        const double adinv = 1.0 / ray_dir[axis];

        double t0 = (ax.min - ray_orig[axis]) * adinv;
        double t1 = (ax.max - ray_orig[axis]) * adinv;

        if (t0 < t1) {
            if (t0 > ray_t.min) ray_t.min = t0;
            if (t1 < ray_t.max) ray_t.max = t1;
        } else {
            if (t1 > ray_t.min) ray_t.min = t1;
            if (t0 < ray_t.max) ray_t.max = t0;
        }

        if (ray_t.max <= ray_t.min)
            return false;
    }
    return true;
}

int Boxes::longest_axis() const {
    if (x.size() > y.size())
        return x.size() > z.size() ? 0 : 2;
    else
        return y.size() > z.size() ? 1 : 2;
}

void Boxes::pad_to_minimums() {
    double delta = 0.0001;
    if (x.size() < delta) x = x.expand(delta);
    if (y.size() < delta) y = y.expand(delta);
    if (z.size() < delta) z = z.expand(delta);
}

Boxes operator+(const Boxes& bbox, const vec3& offset) {
    return Boxes(bbox.x + offset.x(), bbox.y + offset.y(), bbox.z + offset.z());
}

Boxes operator+(const vec3& offset, const Boxes& bbox) {
    return bbox + offset;
}

const Boxes Boxes::empty    = Boxes(interval::empty,    interval::empty,    interval::empty);
const Boxes Boxes::universe = Boxes(interval::universe, interval::universe, interval::universe);
