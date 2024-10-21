/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** interval
*/

#include "interval.hpp"

// Constructors
interval::interval() : min(+infinity), max(-infinity) {}
interval::interval(double min, double max) : min(min), max(max) {}
interval::interval(const interval& a, const interval& b) {
    min = a.min <= b.min ? a.min : b.min;
    max = a.max >= b.max ? a.max : b.max;
}

double interval::size() const {
    return max - min;
}

bool interval::contains(double x) const {
    return min <= x && x <= max;
}

bool interval::surrounds(double x) const {
    return min < x && x < max;
}

double interval::clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

interval interval::expand(double delta) const {
    double padding = delta / 2;
    return interval(min - padding, max + padding);
}

interval operator+(const interval& ival, double displacement) {
    return interval(ival.min + displacement, ival.max + displacement);
}

interval operator+(double displacement, const interval& ival) {
    return ival + displacement;
}

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
