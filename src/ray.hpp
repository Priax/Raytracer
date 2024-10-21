/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** ray
*/

#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

/**
 * @brief Class representing a ray in 3D space.
 */
class ray {
public:
    /**
     * @brief Default constructor for ray.
     */
    ray();

    /**
     * @brief Construct a ray with given origin and direction.
     * 
     * @param origin The origin point of the ray.
     * @param direction The direction vector of the ray.
     */
    ray(const point3& origin, const vec3& direction);

    /**
     * @brief Construct a ray with given origin, direction, and time.
     * 
     * @param origin The origin point of the ray.
     * @param direction The direction vector of the ray.
     * @param time The time value associated with the ray.
     */
    ray(const point3& origin, const vec3& direction, double time);

    /**
     * @brief Get the origin point of the ray.
     * 
     * @return The origin point of the ray.
     */
    const point3& origin() const;

    /**
     * @brief Get the direction vector of the ray.
     * 
     * @return The direction vector of the ray.
     */
    const vec3& direction() const;

    /**
     * @brief Get the point on the ray at a given time.
     * 
     * @param t The time value.
     * @return The point on the ray at time t.
     */
    point3 at(double t) const;

    /**
     * @brief Get the time associated with the ray.
     * 
     * @return The time associated with the ray.
     */
    double time() const { return tm; }

private:
    point3 orig; /**< Origin point of the ray. */
    vec3 dir; /**< Direction vector of the ray. */
    double tm; /**< Time associated with the ray. */
};

#endif
