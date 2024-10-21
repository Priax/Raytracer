/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** ortho
*/

#ifndef ORTHO_HPP
#define ORTHO_HPP

#include "utility.hpp"
#include "vec3.hpp"

/**
 * @brief Class representing an orthonormal frame.
 */
class OrthonormalFrame {
public:
    /**
     * @brief Default constructor.
     */
    OrthonormalFrame();

    /**
     * @brief Accessor operator for the axis vectors.
     * 
     * @param i Index of the axis (0, 1, or 2).
     * @return Reference to the axis vector.
     */
    vec3 operator[](int i) const { return axis[i]; }

    /**
     * @brief Reference accessor operator for the axis vectors.
     * 
     * @param i Index of the axis (0, 1, or 2).
     * @return Reference to the axis vector.
     */
    vec3& operator[](int i) { return axis[i]; }

    /**
     * @brief Get the u-axis vector.
     * 
     * @return The u-axis vector.
     */
    vec3 u() const;

    /**
     * @brief Get the v-axis vector.
     * 
     * @return The v-axis vector.
     */
    vec3 v() const;

    /**
     * @brief Get the w-axis vector.
     * 
     * @return The w-axis vector.
     */
    vec3 w() const;

    /**
     * @brief Convert local coordinates to global coordinates.
     * 
     * @param a Coordinate along the u-axis.
     * @param b Coordinate along the v-axis.
     * @param c Coordinate along the w-axis.
     * @return The global coordinate vector.
     */
    vec3 local(double a, double b, double c) const;

    /**
     * @brief Convert local coordinates to global coordinates.
     * 
     * @param a Local coordinate vector.
     * @return The global coordinate vector.
     */
    vec3 local(const vec3& a) const;

    /**
     * @brief Build the frame from the w-axis vector.
     * 
     * @param w The w-axis vector.
     */
    void build_from_w(const vec3& w);

private:
    vec3 axis[3]; /**< Array of axis vectors (u, v, w). */
};

#endif
