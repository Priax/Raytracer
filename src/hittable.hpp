/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** hittable
*/

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include "interval.hpp"
#include "boxes.hpp"

class material;

/**
 * @brief Represents information about a hit point.
 */
class hit_record {
public:
    point3 p; /**< The hit point. */
    vec3 normal; /**< The normal at the hit point. */
    std::shared_ptr<material> mat; /**< The material of the hit object. */
    double t; /**< The parameter 't' of the ray at the hit point. */
    double u; /**< The u texture coordinate. */
    double v; /**< The v texture coordinate. */
    bool front_face; /**< Indicates if the ray hit the front face of the object. */

    /**
     * @brief Sets the normal direction based on the ray and outward normal.
     * @param r The incident ray.
     * @param outward_normal The outward normal of the hit object.
     */
    void set_face_normal(const ray& r, const vec3& outward_normal);
};

/**
 * @brief Represents a hittable object in the scene.
 */
class hittable {
public:
    virtual ~hittable() = default;

    /**
     * @brief Checks if a ray hits the object.
     * @param r The ray to check for intersection.
     * @param ray_t The interval of the ray.
     * @param rec The hit record to update if a hit is found.
     * @return True if the ray hits the object, false otherwise.
     */
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

    /**
     * @brief Computes the bounding box of the hittable object.
     * @return The bounding box of the object.
     */
    virtual Boxes bounding_box() const = 0;

    /**
     * @brief Computes the probability density function value.
     * @param origin The origin point.
     * @param direction The direction vector.
     * @return The probability density function value.
     */
    virtual double pdf_value(const point3& origin, const vec3& direction) const;

    /**
     * @brief Generates a random direction from the hittable object.
     * @param origin The origin point.
     * @return A random direction vector.
     */
    virtual vec3 random(const point3& origin) const;
};

/**
 * @brief Represents a translation transformation applied to a hittable object.
 */
class translate : public hittable {
public:
    /**
     * @brief Constructs a translation transformation.
     * @param object The hittable object to be translated.
     * @param offset The translation offset.
     */
    translate(std::shared_ptr<hittable> object, const vec3& offset);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;

private:
    std::shared_ptr<hittable> object; /**< The hittable object being translated. */
    vec3 offset; /**< The translation offset. */
    Boxes bbox; /**< The bounding box of the translated object. */
};

/**
 * @brief Represents a rotation transformation applied to a hittable object around the y-axis.
 */
class rotate_y : public hittable {
public:
    /**
     * @brief Constructs a rotation transformation around the y-axis.
     * @param object The hittable object to be rotated.
     * @param angle The rotation angle (in radians).
     */
    rotate_y(std::shared_ptr<hittable> object, double angle);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;

private:
    std::shared_ptr<hittable> object; /**< The hittable object being rotated. */
    double sin_theta; /**< The sine of the rotation angle. */
    double cos_theta; /**< The cosine of the rotation angle. */
    Boxes bbox; /**< The bounding box of the rotated object. */
};

/**
 * @brief Represents a rotation transformation applied to a hittable object around the x-axis.
 */
class rotate_x : public hittable {
public:
    /**
     * @brief Constructs a rotation transformation around the x-axis.
     * @param object The hittable object to be rotated.
     * @param angle The rotation angle (in radians).
     */
    rotate_x(std::shared_ptr<hittable> object, double angle);

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override;
    Boxes bounding_box() const override;

private:
    std::shared_ptr<hittable> object; /**< The hittable object being rotated. */
    double sin_theta; /**< The sine of the rotation angle. */
    double cos_theta; /**< The cosine of the rotation angle. */
    Boxes bbox; /**< The bounding box of the rotated object. */
};

/**
 * @brief Represents a rotation transformation applied to a hittable object around the z-axis.
 */
class rotate_z : public hittable {
public:
    /**
     * @brief Constructs a rotation transformation around the z-axis.
     * @param object The hittable object to be rotated.
     * @param angle The rotation angle (in radians).
     */
    rotate_z(std::shared_ptr<hittable> object, double angle);

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override;
    Boxes bounding_box() const override;

private:
    std::shared_ptr<hittable> object; /**< The hittable object being rotated. */
    double sin_theta; /**< The sine of the rotation angle. */
    double cos_theta; /**< The cosine of the rotation angle. */
    Boxes bbox; /**< The bounding box of the rotated object. */
};

#endif
