#include "sphere.hpp"

// Constructors
sphere::sphere(const point3& center, double radius, std::shared_ptr<material> mat) : center1(center), radius(fmax(0,radius)), mat(mat), is_moving(false) {
    vec3 rvec = vec3(radius, radius, radius);
    bbox = Boxes(center1 - rvec, center1 + rvec);
}

sphere::sphere(const point3& center1, const point3& center2, double radius, std::shared_ptr<material> mat) : center1(center1), radius(fmax(0,radius)), mat(mat), is_moving(true) {
    vec3 rvec = vec3(radius, radius, radius);
    Boxes box1(center1 - rvec, center1 + rvec);
    Boxes box2(center2 - rvec, center2 + rvec);
    bbox = Boxes(box1, box2);

    center_vec = center2 - center1;
}

bool sphere::hit(const ray& r, interval ray_t, hit_record& rec) const {
    point3 center = is_moving ? sphere_center(r.time()) : center1;
    vec3 oc = center - r.origin();
    double a = r.direction().length_squared();
    double h = r.direction().dot(oc);
    double c = oc.length_squared() - radius * radius;

    double discriminant = h * h - a * c;
    if (discriminant < 0)
        return false;

    double sqrtd = sqrt(discriminant);

    double root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root))
            return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    point3 p_outward_normal(outward_normal.x(), outward_normal.y(), outward_normal.z());
    rec.set_face_normal(r, outward_normal);
    get_sphere_uv(p_outward_normal, rec.u, rec.v);
    rec.mat = mat;

    return true;
}

point3 sphere::sphere_center(double time) const {
    return center1 + time * center_vec;
}

void sphere::get_sphere_uv(const point3 &p, double &u, double &v) {
    double theta = acos(-p.y());
    double phi = atan2(-p.z(), p.x()) + pi;

    u = phi / (2 * pi);
    v = theta / pi;
}

Boxes sphere::bounding_box() const { return bbox; }

double sphere::pdf_value(const point3 &origin, const vec3 &direction) const {
    hit_record rec;
    if (!this->hit(ray(origin, direction), interval(0.001, infinity), rec))
        return 0;

    double cos_theta_max = sqrt(1 - radius * radius / (center1 - origin).length_squared());
    double solid_angle = 2 * pi * (1 - cos_theta_max);

    return 1 / solid_angle;
}

vec3 sphere::random(const point3 &origin) const {
    vec3 direction = center1 - origin;
    double distance_squared = direction.length_squared();
    OrthonormalFrame uvw;
    uvw.build_from_w(direction);
    return uvw.local(random_to_sphere(radius, distance_squared));
}

vec3 sphere::random_to_sphere(double radius, double distance_squared) {
    double r1 = Random::random_double();
    double r2 = Random::random_double();
    double z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);

    double phi = 2 * pi * r1;
    double x = cos(phi) * sqrt(1 - z * z);
    double y = sin(phi) * sqrt(1 - z * z);

    return vec3(x, y, z);
}
