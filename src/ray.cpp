#include "ray.hpp"

// Constructors
ray::ray() {}
ray::ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction), tm(0) {}
ray::ray(const point3& origin, const vec3& direction, double time) : orig(origin), dir(direction), tm(time) {}

// Getter for origin
const point3& ray::origin() const {
    //std::clog << orig << std::endl;
    return orig;
}

// Getter for direction
const vec3& ray::direction() const {
    return dir;
}

point3 ray::at(double t) const {
    return orig + t * dir;
}
