/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** color
*/

#ifndef COLOR_H
#define COLOR_H

#include "vec3.hpp"
#include "interval.hpp"

#include <iostream>
#include <list>
#include <mutex>
#include <SFML/Graphics.hpp>

/**
 * @brief Represents a color in RGB space.
 */
class color : public vec3 {
public:
    /**
     * @brief Default constructor. Initializes color components to zero.
     */
    color();

    /**
     * @brief Constructs a color with specified RGB components.
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     */
    color(double r, double g, double b);

    /**
     * @brief Constructs a color with specified RGBA components.
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     * @param a The alpha component.
     */
    color(double r, double g, double b, double a);

    /**
     * @brief Constructs a color from a vec3.
     * @param v The vector representing the color.
     */
    color(const vec3& v);

    /**
     * @brief Gets the alpha component of the color.
     * @return The alpha component of the color.
     */
    double a() const { return e[3]; }

    /**
     * @brief Converts a linear component to gamma space.
     * @param linear_component The linear component to convert.
     * @return The gamma corrected component.
     */
    static double linear_to_gamma(double linear_component);

    /**
     * @brief Writes the color to an output stream in PPM format.
     * @param out The output stream.
     * @param pixel_color The color to write.
     */
    static void write_color(std::ostream &out, const color &pixel_color, std::shared_ptr<std::list<sf::Color>> _colorsQueue, std::shared_ptr<std::mutex> _colorsQueueMutex);

private:
    double alpha; /**< The alpha component of the color. */
};

#endif
