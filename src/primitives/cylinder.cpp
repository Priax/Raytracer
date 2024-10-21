#include "cylinder.hpp"

// LimCylinder Constructors
LimCylinder::LimCylinder(const point3& base, const point3& top, double radius, std::shared_ptr<material> mat) : radius(radius), mat(mat) {
    y_min = fmin(base.y(), top.y());
    y_max = fmax(base.y(), top.y());

    bbox = Boxes(point3(-radius, y_min, -radius), point3(radius, y_max, radius));
}

bool LimCylinder::hit(const ray& r, interval ray_t, hit_record& rec) const {
    point3 origin = r.origin();
    vec3 direction = r.direction();

    double a = direction.x() * direction.x() + direction.z() * direction.z();
    double b = 2 * (origin.x() * direction.x() + origin.z() * direction.z());
    double c = origin.x() * origin.x() + origin.z() * origin.z() - radius * radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);

    double t_min = ray_t.min;
    double t_max = ray_t.max;

    // Check intersection with the side of the cylinder
    double y_hit = origin.y() + t0 * direction.y();
    if (t0 < t_min || t0 > t_max || y_hit < y_min || y_hit > y_max) {
        t0 = (-b + sqrt(discriminant)) / (2 * a);
        y_hit = origin.y() + t1 * direction.y();
        if (t1 < t_min || t1 > t_max || y_hit < y_min || y_hit > y_max)
            return false;
    }

    double t_hit = t0;
    if (t0 < t_min || t0 > t_max) {
        t_hit = t1;
        if (t1 < t_min || t1 > t_max)
            return false;
    }

    point3 hit_point = origin + t_hit * direction;

    // Set normal
    vec3 normal = Vec3Utils::unit_vector(vec3(hit_point.x(), 0, hit_point.z()));

    rec.t = t_hit;
    rec.p = hit_point;
    rec.mat = mat;
    rec.set_face_normal(r, normal);

    return true;
}

Boxes LimCylinder::bounding_box() const {
    return bbox;
}

// Cylinder Constructor
Cylinder::Cylinder(const point3 &base, const point3 &top, double radius, std::shared_ptr<material> mat) : radius(radius), mat(mat) {
    // Déterminer les coordonnées y minimales et maximales du cylindre en tenant compte du rayon
    y_min = fmin(base.y(), top.y()) - radius;
    y_max = fmax(base.y(), top.y()) + radius;

    // Calculer la boîte englobante du cylindre pour l'optimisation de l'accélération de l'intersection
    bbox = Boxes(point3(-radius, y_min, -radius), point3(radius, y_max, radius));
}

bool Cylinder::hit(const ray &r, interval ray_t, hit_record &rec) const {
    point3 origin = r.origin();
    vec3 direction = r.direction();

    double a = direction.x() * direction.x() + direction.z() * direction.z();
    double b = 2 * (origin.x() * direction.x() + origin.z() * direction.z());
    double c = origin.x() * origin.x() + origin.z() * origin.z() - radius * radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);

    double t_min = ray_t.min;
    double t_max = ray_t.max;

    // Check intersection with the side of the cylinder
    double y_hit = origin.y() + t0 * direction.y();
    if (t0 < t_min || t0 > t_max || y_hit < y_min || y_hit > y_max) {
        t0 = (-b + sqrt(discriminant)) / (2 * a);
        y_hit = origin.y() + t1 * direction.y();
        if (t1 < t_min || t1 > t_max || y_hit < y_min || y_hit > y_max)
            return false;
    }

    double t_hit = t0;
    if (t0 < t_min || t0 > t_max) {
        t_hit = t1;
        if (t1 < t_min || t1 > t_max)
            return false;
    }

    point3 hit_point = origin + t_hit * direction;

    // Set normal
    vec3 normal = Vec3Utils::unit_vector(vec3(hit_point.x(), 0, hit_point.z()));

    rec.t = t_hit;
    rec.p = hit_point;
    rec.mat = mat;
    rec.set_face_normal(r, normal);

    // Check intersection with top cap
    double t_cap = (y_max - origin.y()) / direction.y();
    if (t_cap > t_min && t_cap < t_hit) {
        point3 cap_hit_point = origin + t_cap * direction;
        if ((cap_hit_point.x() * cap_hit_point.x() + cap_hit_point.z() * cap_hit_point.z()) <= radius * radius) {
            rec.t = t_cap;
            rec.p = cap_hit_point;
            rec.set_face_normal(r, vec3(0, 1, 0));
            return true;
        }
    }

    // Check intersection with bottom cap
    t_cap = (y_min - origin.y()) / direction.y();
    if (t_cap > t_min && t_cap < t_hit) {
        point3 cap_hit_point = origin + t_cap * direction;
        if ((cap_hit_point.x() * cap_hit_point.x() + cap_hit_point.z() * cap_hit_point.z()) <= radius * radius) {
            rec.t = t_cap;
            rec.p = cap_hit_point;
            rec.set_face_normal(r, vec3(0, -1, 0));
            return true;
        }
    }

    return true;
}

Boxes Cylinder::bounding_box() const {
    return bbox;
}
