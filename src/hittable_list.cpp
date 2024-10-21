/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** hittable_list
*/

#include "hittable_list.hpp"

// Constructors
hittable_list::hittable_list() {}
hittable_list::hittable_list(std::shared_ptr<hittable> object) {
    add(object);
}

void hittable_list::clear() {
    objects.clear();
}

void hittable_list::add(std::shared_ptr<hittable> object) {
    objects.push_back(object);
    bbox = Boxes(bbox, object->bounding_box());
}

bool hittable_list::hit(const ray& r, interval ray_t, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const auto& object : objects) {
        if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

Boxes hittable_list::bounding_box() const { return bbox; }

double hittable_list::pdf_value(const point3& origin, const vec3& direction) const {
    double weight = 1.0 / objects.size();
    double sum = 0.0;

    for (const auto& object : objects)
        sum += weight * object->pdf_value(origin, direction);

    return sum;
}

vec3 hittable_list::random(const point3& origin) const {
    int int_size = int(objects.size());
    return objects[Random::random_int(0, int_size-1)]->random(origin);
}
