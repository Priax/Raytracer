/*
** EPITECH PROJECT, 2024
** rebelotte
** File description:
** cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "../hittable.hpp"
#include "../vec3.hpp"

/**
 * @brief Represents a limited cylinder with flat ends.
 */
class LimCylinder : public hittable {
public:
    /**
     * @brief Constructs a limited cylinder with specified parameters.
     * @param base The base center point of the cylinder.
     * @param top The top center point of the cylinder.
     * @param radius The radius of the cylinder.
     * @param mat The material of the cylinder.
     */
    LimCylinder(const point3& base, const point3& top, double radius, std::shared_ptr<material> mat);

    /**
     * @brief Determines if a ray intersects with the limited cylinder.
     * @param r The ray.
     * @param ray_t The interval of the ray.
     * @param rec The hit record to update if a hit is found.
     * @return True if the ray intersects with the cylinder, false otherwise.
     */
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    /**
     * @brief Computes the bounding box of the limited cylinder.
     * @return The bounding box of the limited cylinder.
     */
    virtual Boxes bounding_box() const override;

private:
    double radius; /**< The radius of the cylinder. */
    double y_min, y_max; /**< The minimum and maximum y-coordinates of the cylinder. */
    std::shared_ptr<material> mat; /**< The material of the cylinder. */
    Boxes bbox; /**< The bounding box of the cylinder. */
};

/**
 * @brief Represents an infinite cylinder.
 */
class Cylinder : public hittable {
public:
    /**
     * @brief Constructs an infinite cylinder with specified parameters.
     * @param base The base center point of the cylinder.
     * @param top The top center point of the cylinder.
     * @param radius The radius of the cylinder.
     * @param mat The material of the cylinder.
     */
    Cylinder(const point3 &base, const point3 &top, double radius, std::shared_ptr<material> mat);

    /**
     * @brief Determines if a ray intersects with the infinite cylinder.
     * @param r The ray.
     * @param ray_t The interval of the ray.
     * @param rec The hit record to update if a hit is found.
     * @return True if the ray intersects with the cylinder, false otherwise.
     */
    virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const override;

    /**
     * @brief Computes the bounding box of the infinite cylinder.
     * @return The bounding box of the infinite cylinder.
     */
    virtual Boxes bounding_box() const override;

private:
    double radius; /**< The radius of the cylinder. */
    double y_min, y_max; /**< The minimum and maximum y-coordinates of the cylinder. */
    std::shared_ptr<material> mat; /**< The material of the cylinder. */
    Boxes bbox; /**< The bounding box of the cylinder. */
};

#endif /* !CYLINDER_HPP_ */
