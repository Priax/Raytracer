/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** triangle
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../hittable.hpp"
#include "../vec3.hpp"
#include "../material.hpp"

/**
 * @brief Represents a triangle in 3D space.
 */
class triangle : public hittable {
public:
    /**
     * @brief Constructs a triangle with specified parameters.
     * @param v0 The first vertex of the triangle.
     * @param v1 The second vertex of the triangle.
     * @param v2 The third vertex of the triangle.
     * @param mat The material of the triangle.
     */
    triangle(const point3& v0, const point3& v1, const point3& v2, std::shared_ptr<material> mat);

    /**
     * @brief Determines if a ray intersects with the triangle.
     * @param r The ray.
     * @param ray_t The interval of the ray.
     * @param rec The hit record to update if a hit is found.
     * @return True if the ray intersects with the triangle, false otherwise.
     */
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    /**
     * @brief Computes the bounding box of the triangle.
     * @return The bounding box of the triangle.
     */
    Boxes bounding_box() const override;

private:
    point3 vertex0, vertex1, vertex2; /**< The vertices of the triangle. */
    std::shared_ptr<material> mat; /**< The material of the triangle. */
    Boxes bbox; /**< The bounding box of the triangle. */

    /**
     * @brief Calculates the normal vector of the triangle.
     * @param v0 The first vertex of the triangle.
     * @param v1 The second vertex of the triangle.
     * @param v2 The third vertex of the triangle.
     * @return The normal vector of the triangle.
     */
    static vec3 calculate_normal(const point3& v0, const point3& v1, const point3& v2);
};

#endif
