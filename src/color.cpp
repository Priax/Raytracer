/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** color
*/

#include "color.hpp"

// Constructor
color::color() : vec3(), alpha(1.0) {}
color::color(double r, double g, double b) : vec3(r, g, b), alpha(1.0) {}
color::color(double r, double g, double b, double a) : vec3(r, g, b), alpha(a) {}
color::color(const vec3& v) : vec3(v), alpha(1.0) {}

double color::linear_to_gamma(double linear_component) {
    return std::sqrt(linear_component);
}

void color::write_color(std::ostream& out, const color& pixel_color, std::shared_ptr<std::list<sf::Color>> _colorsQueue, std::shared_ptr<std::mutex> _colorsQueueMutex) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    if (_colorsQueue != nullptr) {
        std::lock_guard guard(*_colorsQueueMutex);
    }

    if (r != r) r = 0.0;
    if (g != g) g = 0.0;
    if (b != b) b = 0.0;

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

    if (_colorsQueue != nullptr) {
        _colorsQueue->push_back(sf::Color(rbyte, gbyte, bbyte));
    }
}
