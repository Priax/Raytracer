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
#include <algorithm>
#include <vector>

/**
 * @brief Bounding Volume Hierarchy node for fast ray-object intersection.
 */
class bvh_node : public hittable {
public:
    bvh_node(hittable_list list);
    bvh_node(std::vector<std::shared_ptr<hittable>>& objects, size_t start, size_t end);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;

private:
    std::shared_ptr<hittable> left;
    std::shared_ptr<hittable> right;
    Boxes bbox;

    static bool box_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b, int axis);
};

#endif
