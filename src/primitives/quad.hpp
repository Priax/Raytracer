#ifndef QUAD_H
#define QUAD_H

#include "../utility.hpp"
#include "../hittable.hpp"
#include "../hittable_list.hpp"
#include "../vec3.hpp"

/**
 * @brief Represents a quadrilateral in 3D space.
 */
class quad : public hittable {
public:
    /**
     * @brief Constructs a quadrilateral with specified parameters.
     * @param Q A point on the quadrilateral.
     * @param u The first direction vector.
     * @param v The second direction vector.
     * @param mat The material of the quadrilateral.
     */
    quad(const point3& Q, const vec3& u, const vec3& v, std::shared_ptr<material> mat);

    virtual void set_bounding_box(); /**< Sets the bounding box of the quadrilateral. */
    Boxes bounding_box() const override; /**< Computes the bounding box of the quadrilateral. */
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override; /**< Determines if a ray intersects with the quadrilateral. */
    virtual bool is_interior(double a, double b, hit_record& rec) const; /**< Checks if a point is inside the quadrilateral. */
    virtual double pdf_value(const point3& origin, const vec3& direction) const override; /**< Computes the probability density function value. */
    virtual vec3 random(const point3& origin) const override; /**< Generates a random point on the quadrilateral. */

private:
    point3 Q; /**< A point on the quadrilateral. */
    vec3 u, v, w; /**< Direction vectors. */
    std::shared_ptr<material> mat; /**< The material of the quadrilateral. */
    Boxes bbox; /**< The bounding box of the quadrilateral. */
    vec3 normal; /**< The normal vector of the quadrilateral. */
    double D; /**< Distance from the origin to the plane of the quadrilateral. */
    double area; /**< The area of the quadrilateral. */
};

/**
 * @brief Represents a cube composed of six quadrilateral sides.
 */
class Cube : public hittable {
public:
    /**
     * @brief Constructs a cube with specified parameters.
     * @param a The minimum point of the cube.
     * @param b The maximum point of the cube.
     * @param mat The material of the cube.
     */
    Cube(const point3& a, const point3& b, std::shared_ptr<material> mat);

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const override; /**< Determines if a ray intersects with the cube. */
    virtual Boxes bounding_box() const override; /**< Computes the bounding box of the cube. */

private:
    hittable_list sides; /**< The list of quadrilateral sides of the cube. */
    std::shared_ptr<material> mat; /**< The material of the cube. */
    Boxes bbox; /**< The bounding box of the cube. */
};

#endif
