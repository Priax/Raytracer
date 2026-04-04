#include "ray.hpp"

// Constructors
ray::ray() {}
ray::ray(const point3& origin, const vec3& direction)
    : orig(origin), dir(direction),
      inv_d(vec3(1.0 / direction.x(), 1.0 / direction.y(), 1.0 / direction.z())),
      tm(0) {}
ray::ray(const point3& origin, const vec3& direction, double time)
    : orig(origin), dir(direction),
      inv_d(vec3(1.0 / direction.x(), 1.0 / direction.y(), 1.0 / direction.z())),
      tm(time) {}

// Getter for origin
const point3& ray::origin() const {
    //std::clog << orig << std::endl;
    return orig;
}

// Getter for direction
const vec3& ray::direction() const {
    return dir;
}

const vec3& ray::inv_dir() const {
    return inv_d;
}

point3 ray::at(double t) const {
    return orig + t * dir;
}
