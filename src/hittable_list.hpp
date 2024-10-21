/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** hittable_list
*/

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.hpp"
#include "boxes.hpp"

#include <memory>
#include <vector>

/**
 * @brief Represents a list of hittable objects.
 */
class hittable_list : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects; /**< List of hittable objects. */

    /**
     * @brief Default constructor. Creates an empty list.
     */
    hittable_list();

    /**
     * @brief Constructs a list with a single hittable object.
     * @param object The hittable object to add to the list.
     */
    hittable_list(std::shared_ptr<hittable> object);

    /**
     * @brief Clears the list of hittable objects.
     */
    void clear();

    /**
     * @brief Adds a hittable object to the list.
     * @param object The hittable object to add.
     */
    void add(std::shared_ptr<hittable> object);

    /**
     * @brief Determines if a ray intersects with any object in the list.
     * @param r The ray.
     * @param ray_t The interval of the ray.
     * @param rec The hit record to update if a hit is found.
     * @return True if the ray intersects with any object in the list, false otherwise.
     */
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    /**
     * @brief Computes the bounding box of the list of hittable objects.
     * @return The bounding box of the list.
     */
    Boxes bounding_box() const override;

    /**
     * @brief Computes the probability density function value.
     * @param origin The origin point.
     * @param direction The direction vector.
     * @return The probability density function value.
     */
    double pdf_value(const point3& origin, const vec3& direction) const override;

    /**
     * @brief Generates a random direction from the list of hittable objects.
     * @param origin The origin point.
     * @return A random direction vector.
     */
    vec3 random(const point3& origin) const override;

private:
    Boxes bbox; /**< The bounding box of the list of hittable objects. */
};

#endif
