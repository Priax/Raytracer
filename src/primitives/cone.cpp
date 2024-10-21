/*
** EPITECH PROJECT, 2024
** rebelotte
** File description:
** cone
*/
#include "cone.hpp"

// Cone Constructors
LimCone::LimCone(point3 _center, double _radius, double _height) : center(_center), radius(_radius), height(_height) {}

LimCone::LimCone(point3 _center, double _radius, double _height, std::shared_ptr<material> _material) : center(_center), radius(_radius), height(_height), mat(_material) {
    bounding_box();
}

bool LimCone::hit(const ray &r, interval ray_t, hit_record &rec) const {
    if (!bounding_box().hit(r, ray_t))
        return false;

    vec3 oc = r.origin() - center;
    double k = radius / height;
    double k2 = k * k;
    double a = r.direction().dot(r.direction()) - k2 * r.direction().dot(vec3(0, 1, 0)) * r.direction().dot(vec3(0, 1, 0));
    double b = 2 * (oc.dot(r.direction()) - k2 * oc.dot(vec3(0, 1, 0)) * r.direction().dot(vec3(0, 1, 0)));
    double c = oc.dot(oc) - k2 * oc.dot(vec3(0, 1, 0)) * oc.dot(vec3(0, 1, 0));

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;

    double root = (-b - std::sqrt(discriminant)) / (2 * a);
    if (!ray_t.surrounds(root))
    {
        root = (-b + std::sqrt(discriminant)) / (2 * a);
        if (!ray_t.surrounds(root))
            return false;
    }

    // Check if the intersection is within the height of the cone
    double intersection_y = r.at(root).y();
    if (intersection_y < center.y() || intersection_y > center.y() + height)
        return false;

    // Fill hit_record
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = normal_at(rec.p);
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;

    return true;
}

Boxes LimCone::bounding_box() const {
    point3 min_point(center.x() - radius, center.y() - radius, center.z() - radius);
    point3 max_point(center.x() + radius, center.y() + height + radius, center.z() + radius);
    return Boxes(min_point, max_point);
}

vec3 LimCone::normal_at(const point3& p) const {
    vec3 n = (p - center).normalized();
    n[1] = radius / height;
    return n;
}

// Cone Constructor
Cone::Cone(const point3& base_center, double base_radius, double _height, std::shared_ptr<material> _material) : center(base_center), radius(base_radius), height(_height), mat(_material) {
        bbox = bounding_box();
}

bool Cone::hit(const ray &r, interval ray_t, hit_record &rec) const {
    if (!bbox.hit(r, ray_t))
        return false;

    vec3 oc = r.origin() - center;
    double k = radius / height;
    double k2 = k * k;
    double a = r.direction().dot(r.direction()) - k2 * r.direction().dot(vec3(0, 1, 0)) * r.direction().dot(vec3(0, 1, 0));
    double b = 2 * (oc.dot(r.direction()) - k2 * oc.dot(vec3(0, 1, 0)) * r.direction().dot(vec3(0, 1, 0)));
    double c = oc.dot(oc) - k2 * oc.dot(vec3(0, 1, 0)) * oc.dot(vec3(0, 1, 0));

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;

    double root = (-b - std::sqrt(discriminant)) / (2 * a);
    if (!ray_t.surrounds(root)) {
        root = (-b + std::sqrt(discriminant)) / (2 * a);
        if (!ray_t.surrounds(root))
            return false;
    }

    // Check if the intersection is within the height of the cone
    double intersection_y = r.at(root).y();
    if (intersection_y < center.y() || intersection_y > center.y() + height) {
        // Check if the intersection is on the base of the cone
        double base_hit_t = (center.y() - r.origin().y()) / r.direction().y();
        point3 base_hit_point = r.at(base_hit_t);
        if ((base_hit_point - center).length_squared() <= radius * radius) {
            rec.t = base_hit_t;
            rec.p = base_hit_point;
            vec3 outward_normal = normal_at(base_hit_point);
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;
            return true;
        }
        // Check if the intersection is on the top base of the cone
        double top_hit_t = (center.y() + height - r.origin().y()) / r.direction().y();
        point3 top_hit_point = r.at(top_hit_t);
        if ((top_hit_point - center).length_squared() <= radius * radius) {
            rec.t = top_hit_t;
            rec.p = top_hit_point;
            vec3 outward_normal = normal_at(top_hit_point);
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;
            return true;
        }
        return false;
    }

    // Fill hit_record
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = normal_at(rec.p);
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;

    return true;
}

Boxes Cone::bounding_box() const {
    point3 min_point(center.x() - radius, center.y(), center.z() - radius);
    point3 max_point(center.x() + radius, center.y() + height, center.z() + radius);
    return Boxes(min_point, max_point);
}

vec3 Cone::normal_at(const point3& p) const {
    double dist_to_center = (p - center).length();
    if (dist_to_center < radius) {
        // Normal on base
        return vec3(0, -1, 0);
    } else if (dist_to_center > radius && dist_to_center < radius + height) {
        // Normal on lateral surface
        vec3 n = (p - center).normalized();
        n[1] = radius / height;
        return n;
    } else {
        // Normal on top
        return vec3(0, 1, 0);
    }
}
