/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** hittable
*/

#include "hittable.hpp"

double hittable::pdf_value(const point3& origin, const vec3& direction) const {
    (void)origin;
    (void)direction;
    return 0.0;
}

vec3 hittable::random(const point3& origin) const {
    (void)origin;
    return vec3(1, 0, 0);
}

void hit_record::set_face_normal(const ray& r, const vec3& outward_normal) {
    front_face = r.direction().dot(outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}

// Translate Constructors
translate::translate(std::shared_ptr<hittable> object, const vec3& offset) : object(object), offset(offset) {
    bbox = object->bounding_box() + offset;
}

bool translate::hit(const ray &r, interval ray_t, hit_record &rec) const {
    ray offset_r(r.origin() - offset, r.direction(), r.time());

    if (!object->hit(offset_r, ray_t, rec))
        return false;

    rec.p += offset;

    return true;
}

Boxes translate::bounding_box() const { return bbox; }

// Rotate_y Constructors

rotate_y::rotate_y(std::shared_ptr<hittable> object, double angle) : object(object) {
    double radians = Random::degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    bbox = object->bounding_box();

    point3 min(infinity, infinity, infinity);
    point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                double x = i * bbox.x.max + (1 - i) * bbox.x.min;
                double y = j * bbox.y.max + (1 - j) * bbox.y.min;
                double z = k * bbox.z.max + (1 - k) * bbox.z.min;
                double newx = cos_theta * x + sin_theta * z;
                double newz = -sin_theta * x + cos_theta * z;
                vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }
    bbox = Boxes(min, max);
}

bool rotate_y::hit(const ray &r, interval ray_t, hit_record &rec) const {
    point3 origin = r.origin();
    vec3 direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

    ray rotated_r(origin, direction, r.time());

    // Determine whether an intersection exists in object space (and if so, where)
    if (!object->hit(rotated_r, ray_t, rec))
        return false;

    // Change the intersection point from object space to world space
    point3 p = rec.p;
    p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
    p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

    // Change the normal from object space to world space
    vec3 normal = rec.normal;
    normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.normal = normal;

    return true;
}

Boxes rotate_y::bounding_box() const { return bbox; }

// Rotate_x constructor

rotate_x::rotate_x(std::shared_ptr<hittable> object, double angle) : object(object) {
    double radians = Random::degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    bbox = object->bounding_box();

    point3 min(infinity, infinity, infinity);
    point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                double x = i * bbox.x.max + (1 - i) * bbox.x.min;
                double y = j * bbox.y.max + (1 - j) * bbox.y.min;
                double z = k * bbox.z.max + (1 - k) * bbox.z.min;
                double newy = cos_theta * y - sin_theta * z;
                double newz = sin_theta * y + cos_theta * z;
                vec3 tester(x, newy, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }
    bbox = Boxes(min, max);
}

bool rotate_x::hit(const ray &r, interval ray_t, hit_record &rec) const {
    point3 origin = r.origin();
    vec3 direction = r.direction();

    origin[1] = cos_theta * r.origin()[1] - sin_theta * r.origin()[2];
    origin[2] = sin_theta * r.origin()[1] + cos_theta * r.origin()[2];

    direction[1] = cos_theta * r.direction()[1] - sin_theta * r.direction()[2];
    direction[2] = sin_theta * r.direction()[1] + cos_theta * r.direction()[2];

    ray rotated_r(origin, direction, r.time());

    if (!object->hit(rotated_r, ray_t, rec))
        return false;

    point3 p = rec.p;
    p[1] = cos_theta * rec.p[1] + sin_theta * rec.p[2];
    p[2] = -sin_theta * rec.p[1] + cos_theta * rec.p[2];

    vec3 normal = rec.normal;
    normal[1] = cos_theta * rec.normal[1] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[1] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.normal = normal;

    return true;
}

Boxes rotate_x::bounding_box() const { return bbox; }

// Rotate_z Constructor

rotate_z::rotate_z(std::shared_ptr<hittable> object, double angle) : object(object) {
    double radians = Random::degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    bbox = object->bounding_box();

    point3 min(infinity, infinity, infinity);
    point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                double x = i * bbox.x.max + (1 - i) * bbox.x.min;
                double y = j * bbox.y.max + (1 - j) * bbox.y.min;
                double z = k * bbox.z.max + (1 - k) * bbox.z.min;
                double newx = cos_theta * x - sin_theta * y;
                double newy = sin_theta * x + cos_theta * y;
                vec3 tester(newx, newy, z);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }
    bbox = Boxes(min, max);
}

bool rotate_z::hit(const ray &r, interval ray_t, hit_record &rec) const {
    point3 origin = r.origin();
    vec3 direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[1];
    origin[1] = sin_theta * r.origin()[0] + cos_theta * r.origin()[1];

    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[1];
    direction[1] = sin_theta * r.direction()[0] + cos_theta * r.direction()[1];

    ray rotated_r(origin, direction, r.time());

    if (!object->hit(rotated_r, ray_t, rec))
        return false;

    point3 p = rec.p;
    p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[1];
    p[1] = -sin_theta * rec.p[0] + cos_theta * rec.p[1];

    vec3 normal = rec.normal;
    normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[1];
    normal[1] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[1];

    rec.p = p;
    rec.normal = normal;

    return true;
}

Boxes rotate_z::bounding_box() const { return bbox; }
