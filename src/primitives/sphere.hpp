#ifndef SPHERE_H
#define SPHERE_H

#include "../hittable.hpp"
#include "../vec3.hpp"
#include "../material.hpp"

/**
 * @brief Represents a sphere in 3D space.
 */
class sphere : public hittable {
public:
    // Stationary Sphere
    /**
     * @brief Constructs a stationary sphere with specified parameters.
     * @param center The center point of the sphere.
     * @param radius The radius of the sphere.
     * @param mat The material of the sphere.
     */
    sphere(const point3& center, double radius, std::shared_ptr<material> mat);
    // Moving Sphere
    /**
     * @brief Constructs a moving sphere with specified parameters.
     * @param center1 The center point of the sphere at time 0.
     * @param center2 The center point of the sphere at time 1.
     * @param radius The radius of the sphere.
     * @param mat The material of the sphere.
     */
    sphere(const point3& center1, const point3& center2, double radius, std::shared_ptr<material> mat);

    /**
     * @brief Determines if a ray intersects with the sphere.
     * @param r The ray.
     * @param ray_t The interval of the ray.
     * @param rec The hit record to update if a hit is found.
     * @return True if the ray intersects with the sphere, false otherwise.
     */
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    /**
     * @brief Computes the bounding box of the sphere.
     * @return The bounding box of the sphere.
     */
    Boxes bounding_box() const override;

    /**
     * @brief Computes the probability density function value.
     * @param origin The origin point.
     * @param direction The direction vector.
     * @return The probability density function value.
     */
    double pdf_value(const point3 &origin, const vec3 &direction) const override;

    /**
     * @brief Generates a random point on the sphere.
     * @param origin The origin point.
     * @return A random point on the sphere.
     */
    vec3 random(const point3 &origin) const override;

private:
    point3 center1; /**< The center point of the sphere at time 0. */
    double radius; /**< The radius of the sphere. */
    std::shared_ptr<material> mat; /**< The material of the sphere. */
    bool is_moving; /**< Indicates whether the sphere is moving. */
    vec3 center_vec; /**< The vector between center1 and center2. */
    Boxes bbox; /**< The bounding box of the sphere. */

    /**
     * @brief Computes the center point of the sphere at a given time.
     * @param time The time parameter.
     * @return The center point of the sphere at the specified time.
     */
    point3 sphere_center(double time) const;

    /**
     * @brief Computes the u and v coordinates on the sphere for a given point.
     * @param p The point on the sphere.
     * @param u The u coordinate.
     * @param v The v coordinate.
     */
    static void get_sphere_uv(const point3& p, double& u, double& v);

    /**
     * @brief Generates a random point on the sphere given the radius and squared distance.
     * @param radius The radius of the sphere.
     * @param distance_squared The squared distance.
     * @return A random point on the sphere.
     */
    static vec3 random_to_sphere(double radius, double distance_squared);
};

#endif
