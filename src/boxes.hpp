/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** boxes
*/

#ifndef BOXES_H
#define BOXES_H

#include "utility.hpp"
#include "interval.hpp"
#include "vec3.hpp"
#include "ray.hpp"

/**
 * @brief Represents an axis-aligned bounding box in 3D space.
 */
class Boxes {
public:
    interval x, y, z; /**< Intervals along the x, y, and z axes. */

    /**
     * @brief Default constructor. Creates an empty bounding box.
     */
    Boxes();

    /**
     * @brief Constructs a bounding box with specified intervals along the x, y, and z axes.
     * @param x The interval along the x axis.
     * @param y The interval along the y axis.
     * @param z The interval along the z axis.
     */
    Boxes(const interval& x, const interval& y, const interval& z);

    /**
     * @brief Constructs a bounding box from two points defining its diagonal.
     * @param a One corner of the bounding box.
     * @param b The opposite corner of the bounding box.
     */
    Boxes(const point3& a, const point3& b);

    /**
     * @brief Constructs a bounding box that encloses two given bounding boxes.
     * @param box0 The first bounding box.
     * @param box1 The second bounding box.
     */
    Boxes(const Boxes& box0, const Boxes& box1);

    /**
     * @brief Returns the interval along the specified axis.
     * @param n The axis index (0 for x, 1 for y, 2 for z).
     * @return The interval along the specified axis.
     */
    const interval& axis_interval(int n) const;

    /**
     * @brief Checks if a ray intersects with the bounding box within a given interval.
     * @param r The ray.
     * @param ray_t The interval of the ray.
     * @return True if the ray intersects with the bounding box within the interval, false otherwise.
     */
    bool hit(const ray& r, interval ray_t) const;

    /**
     * @brief Determines the longest axis of the bounding box.
     * @return The index of the longest axis (0 for x, 1 for y, 2 for z).
     */
    int longest_axis() const;

    static const Boxes empty, universe; /**< Static instances of an empty bounding box and the universe bounding box. */

private:
    /**
     * @brief Pads the bounding box to ensure that the intervals are not degenerate.
     */
    void pad_to_minimums();
};

/**
 * @brief Overloaded operator to translate a bounding box by a vector offset.
 * @param bbox The bounding box.
 * @param offset The offset vector.
 * @return The translated bounding box.
 */
Boxes operator+(const Boxes& bbox, const vec3& offset);

/**
 * @brief Overloaded operator to translate a bounding box by a vector offset.
 * @param offset The offset vector.
 * @param bbox The bounding box.
 * @return The translated bounding box.
 */
Boxes operator+(const vec3& offset, const Boxes& bbox);

#endif
