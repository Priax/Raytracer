/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** pyramide
*/

#ifndef PYRAMIDE_HPP_
#define PYRAMIDE_HPP_

#include "../hittable.hpp"
#include "../hittable_list.hpp"
#include "triangle.hpp"
#include "quad.hpp"

/**
 * @brief Represents a pyramid composed of triangular sides.
 */
class pyramide : public hittable {
private:
    std::shared_ptr<material> mat; /**< The material of the pyramid. */
    hittable_list sides; /**< The list of triangular sides of the pyramid. */
    Boxes bbox; /**< The bounding box of the pyramid. */
public:
    /**
     * @brief Constructs a pyramid with specified parameters.
     * @param summit The summit point of the pyramid.
     * @param basis1 The first basis point of the pyramid.
     * @param basis2 The second basis point of the pyramid.
     * @param basis3 The third basis point of the pyramid.
     * @param basis4 The fourth basis point of the pyramid.
     * @param mat The material of the pyramid.
     */
    pyramide(point3 summit, point3 basis1, point3 basis2, point3 basis3, point3 basis4, std::shared_ptr<material> mat);

    /**
     * @brief Determines if a ray intersects with the pyramid.
     * @param r The ray.
     * @param ray_t The interval of the ray.
     * @param rec The hit record to update if a hit is found.
     * @return True if the ray intersects with the pyramid, false otherwise.
     */
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const override { return sides.hit(r, ray_t, rec); }

    /**
     * @brief Computes the bounding box of the pyramid.
     * @return The bounding box of the pyramid.
     */
    virtual Boxes bounding_box() const override;
};

#endif /* !PYRAMIDE_HPP_ */
