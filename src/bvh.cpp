/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** bvh
*/

#include "bvh.hpp"

bvh_node::bvh_node(hittable_list list)
    : bvh_node(list.objects, 0, list.objects.size())
{
}

bvh_node::bvh_node(std::vector<std::shared_ptr<hittable>>& objects, size_t start, size_t end)
{
    bbox = Boxes::empty;
    for (size_t i = start; i < end; i++)
        bbox = Boxes(bbox, objects[i]->bounding_box());

    int axis = bbox.longest_axis();
    size_t span = end - start;

    if (span == 1) {
        left = right = objects[start];
    } else if (span == 2) {
        left = objects[start];
        right = objects[start + 1];
    } else {
        std::sort(objects.begin() + start, objects.begin() + end,
            [axis](const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b) {
                return box_compare(a, b, axis);
            });
        size_t mid = start + span / 2;
        left  = std::make_shared<bvh_node>(objects, start, mid);
        right = std::make_shared<bvh_node>(objects, mid, end);
    }
}

bool bvh_node::hit(const ray& r, interval ray_t, hit_record& rec) const
{
    if (!bbox.hit(r, ray_t))
        return false;
    bool hit_left  = left->hit(r, ray_t, rec);
    bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);
    return hit_left || hit_right;
}

Boxes bvh_node::bounding_box() const
{
    return bbox;
}

bool bvh_node::box_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b, int axis)
{
    return a->bounding_box().axis_interval(axis).min < b->bounding_box().axis_interval(axis).min;
}
