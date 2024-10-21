/*
** EPITECH PROJECT, 2024
** cpp
** File description:
** cone
*/

#ifndef CONE_H_
#define CONE_H_

#include "../hittable.hpp" // Include the base class for hittable objects
#include "../vec3.hpp" // Include the definition of vec3 class
#include "../boxes.hpp" // Include the definition of Boxes class

/**
 * @brief Represents a cone with limited height (open cone).
 */
class LimCone : public hittable {
public:
    /**
     * @brief Constructs a limited cone with the specified center, radius, and height.
     * 
     * @param _center The center of the cone.
     * @param _radius The radius of the cone.
     * @param _height The height of the cone.
     */
    LimCone(point3 _center, double _radius, double _height);

    /**
     * @brief Constructs a limited cone with the specified center, radius, height, and material.
     * 
     * @param _center The center of the cone.
     * @param _radius The radius of the cone.
     * @param _height The height of the cone.
     * @param _material The material of the cone.
     */
    LimCone(point3 _center, double _radius, double _height, std::shared_ptr<material> _material);

    /**
     * @brief Checks if the cone is hit by the given ray.
     * 
     * @param r The ray to check for intersection.
     * @param ray_t The interval for the ray.
     * @param rec The hit record to populate if intersection occurs.
     * @return True if the cone is hit, false otherwise.
     */
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    /**
     * @brief Computes the bounding box of the cone.
     * 
     * @return The bounding box of the cone.
     */
    virtual Boxes bounding_box() const override;

private:
    point3 center; ///< The center of the cone.
    double radius; ///< The radius of the cone.
    double height; ///< The height of the cone.
    std::shared_ptr<material> mat; ///< The material of the cone.
    Boxes bbox; ///< The bounding box of the cone.

    /**
     * @brief Computes the normal vector at a given point on the cone surface.
     * 
     * @param p The point on the cone surface.
     * @return The normal vector at the given point.
     */
    vec3 normal_at(const point3& p) const;
};

/**
 * @brief Represents a cone with closed base (closed cone).
 */
class Cone : public hittable {
public:
    /**
     * @brief Constructs a cone with the specified base center, base radius, height, and material.
     * 
     * @param base_center The center of the cone's base.
     * @param base_radius The radius of the cone's base.
     * @param _height The height of the cone.
     * @param _material The material of the cone.
     */
    Cone(const point3& base_center, double base_radius, double _height, std::shared_ptr<material> _material);

    /**
     * @brief Checks if the cone is hit by the given ray.
     * 
     * @param r The ray to check for intersection.
     * @param ray_t The interval for the ray.
     * @param rec The hit record to populate if intersection occurs.
     * @return True if the cone is hit, false otherwise.
     */
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override;

    /**
     * @brief Computes the bounding box of the cone.
     * 
     * @return The bounding box of the cone.
     */
    virtual Boxes bounding_box() const override;

private:
    point3 center; ///< The center of the cone's base.
    double radius; ///< The radius of the cone's base.
    double height; ///< The height of the cone.
    std::shared_ptr<material> mat; ///< The material of the cone.
    Boxes bbox; ///< The bounding box of the cone.

    /**
     * @brief Computes the normal vector at a given point on the cone surface.
     * 
     * @param p The point on the cone surface.
     * @return The normal vector at the given point.
     */
    vec3 normal_at(const point3& p) const;
};

#endif /* !CONE_H_ */
