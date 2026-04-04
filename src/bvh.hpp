/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** bvh
*/

#ifndef BVH_H
#define BVH_H

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "primitives/triangle.hpp"
#include <algorithm>
#include <vector>
#include <limits>

/**
 * @brief Bounding Volume Hierarchy node for fast ray-object intersection.
 */
class bvh_node : public hittable {
public:
    bvh_node(hittable_list list);
    bvh_node(std::vector<std::shared_ptr<hittable>>& objects, size_t start, size_t end);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;

    int max_depth() const;
    size_t node_count() const;

private:
    std::shared_ptr<hittable> left;
    std::shared_ptr<hittable> right;
    Boxes bbox;

    static bool box_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b, int axis);
};


// ─── Flat triangle (no virtual dispatch, no heap per object) ─────────────────

struct FlatTriangle {
    point3 v0, v1, v2;
    vec3   normal;
    vec3   uv0, uv1, uv2;
    const material *mat;
    bool   has_uvs;

    explicit FlatTriangle(const triangle& t)
        : v0(t.get_v0()), v1(t.get_v1()), v2(t.get_v2()),
          normal(t.get_normal()),
          uv0(t.get_uv0()), uv1(t.get_uv1()), uv2(t.get_uv2()),
          mat(t.get_mat().get()), has_uvs(t.get_has_uvs()) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const;
};

// ─── Linear (flat) BVH ────────────────────────────────────────────────────────
//
// Nodes are stored in DFS pre-order: the left child of node[i] is always
// node[i+1], and the right child index is stored in node[i].offset.
// This layout maximises cache locality during traversal.
//
class LinearBVH : public hittable {
public:
    struct Node {
        Boxes    bounds;
        int      offset;      // leaf  → first primitive index
                              // inner → right-child node index
        uint16_t n_prims;     // 0 = inner node
        uint8_t  split_axis;
        uint8_t  _pad{};
    };

    explicit LinearBVH(hittable_list& mesh);

    bool  hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;

    size_t node_count()  const { return nodes.size(); }
    size_t prim_count()  const { return prims.size(); }

private:
    std::vector<Node>                      nodes;
    std::vector<FlatTriangle>              prims;
    std::vector<std::shared_ptr<material>> mat_owner; // keeps materials alive

    int build(std::vector<std::shared_ptr<hittable>>& objs,
              size_t start, size_t end);
};

#endif
