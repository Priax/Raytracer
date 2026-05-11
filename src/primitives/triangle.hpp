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
     * @brief Flat-shaded triangle, no UVs.
     */
    triangle(const point3& v0, const point3& v1, const point3& v2,
             std::shared_ptr<material> mat);
 
    /**
     * @brief Flat-shaded triangle with per-vertex UV coordinates.
     * UVs are vec3(u, v, 0).
     */
    triangle(const point3& v0, const point3& v1, const point3& v2,
             const vec3& uv0, const vec3& uv1, const vec3& uv2,
             std::shared_ptr<material> mat);
 
    /**
     * @brief Smooth-shaded triangle with per-vertex normals and UV coordinates.
     * Normals are interpolated barycentrically in hit(), giving Phong-style
     * smooth shading even on coarse meshes (e.g. parametric surfaces).
     * UVs are vec3(u, v, 0).
     */
    triangle(const point3& v0, const point3& v1, const point3& v2,
             const vec3& uv0, const vec3& uv1, const vec3& uv2,
             const vec3& n0,  const vec3& n1,  const vec3& n2,
             std::shared_ptr<material> mat);

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

    const point3& get_v0()     const { return vertex0; }
    const point3& get_v1()     const { return vertex1; }
    const point3& get_v2()     const { return vertex2; }
    const vec3&   get_normal() const { return precomputed_normal; }
    const vec3&   get_uv0()    const { return uv0; }
    const vec3&   get_uv1()    const { return uv1; }
    const vec3&   get_uv2()    const { return uv2; }
    bool          get_has_uvs()const { return has_uvs; }
    const std::shared_ptr<material>& get_mat() const { return mat; }

private:
    point3 vertex0, vertex1, vertex2; /**< The vertices of the triangle. */
    vec3 uv0, uv1, uv2;              /**< Per-vertex UV texture coordinates. */
    vec3 vn0, vn1, vn2;            /**< Per-vertex normals (smooth shading) */
    bool has_uvs = false;            /**< Whether UV coordinates were provided. */
    bool has_vnorms = false;        /**< True when per-vertex normals were supplied */
    std::shared_ptr<material> mat;   /**< The material of the triangle. */
    Boxes bbox;                      /**< The bounding box of the triangle. */
    vec3 precomputed_normal;         /**< Unit normal, precomputed at construction time. */

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
