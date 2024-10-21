#include "quad.hpp"

quad::quad(const point3& Q, const vec3& u, const vec3& v, std::shared_ptr<material> mat) : Q(Q), u(u), v(v), mat(mat) {
    vec3 n = u.cross(v);
    normal = Vec3Utils::unit_vector(n);
    D = normal.dot(Q);
    w = n / n.dot(n);

    area = n.length();

    set_bounding_box();
}

void quad::set_bounding_box() {
    Boxes bbox_diagonal1 = Boxes(Q, Q + u + v);
    Boxes bbox_diagonal2 = Boxes(Q + u, Q + v);
    bbox = Boxes(bbox_diagonal1, bbox_diagonal2);
}

Boxes quad::bounding_box() const {
    return bbox;
}

bool quad::hit(const ray& r, interval ray_t, hit_record& rec) const {
    double denom = normal.dot(r.direction());

    if (fabs(denom) < 1e-8)
       return false;

    double t = (D - normal.dot(r.origin())) / denom;
    if (!ray_t.contains(t))
        return false;

    point3 intersection = r.at(t);
    vec3 planar_hitpt_vector = intersection - Q;
    double alpha = w.dot(planar_hitpt_vector.cross(v));
    double beta = w.dot(u.cross(planar_hitpt_vector));

    if (!is_interior(alpha, beta, rec))
        return false;
    rec.t = t;
    rec.p = intersection;
    rec.mat = mat;
    rec.set_face_normal(r, normal);
    return true;
}

bool quad::is_interior(double a, double b, hit_record& rec) const {
    interval unit_interval = interval(0, 1);

    if (!unit_interval.contains(a) || !unit_interval.contains(b))
        return false;

    rec.u = a;
    rec.v = b;
    return true;
}

double quad::pdf_value(const point3& origin, const vec3& direction) const {
    hit_record rec;
    if (!this->hit(ray(origin, direction), interval(0.001, infinity), rec))
        return 0;

    double distance_squared = rec.t * rec.t * direction.length_squared();
    double cosine = fabs(direction.dot(rec.normal) / direction.length());

    return distance_squared / (cosine * area);
}

vec3 quad::random(const point3& origin) const {
    point3 p = Q + (Random::random_double() * u) + (Random::random_double() * v);
    return p - origin;
}

// Cube Constructor
Cube::Cube(const point3 &a, const point3 &b, std::shared_ptr<material> mat) : mat(mat) {
    point3 min = point3(fmin(a.x(), b.x()), fmin(a.y(), b.y()), fmin(a.z(), b.z()));
    point3 max = point3(fmax(a.x(), b.x()), fmax(a.y(), b.y()), fmax(a.z(), b.z()));

    vec3 dx = vec3(max.x() - min.x(), 0, 0);
    vec3 dy = vec3(0, max.y() - min.y(), 0);
    vec3 dz = vec3(0, 0, max.z() - min.z());

    sides.add(std::make_shared<quad>(point3(min.x(), min.y(), max.z()), dx, dy, mat));  // front
    sides.add(std::make_shared<quad>(point3(max.x(), min.y(), max.z()), -dz, dy, mat)); // right
    sides.add(std::make_shared<quad>(point3(max.x(), min.y(), min.z()), -dx, dy, mat)); // back
    sides.add(std::make_shared<quad>(point3(min.x(), min.y(), min.z()), dz, dy, mat));  // left
    sides.add(std::make_shared<quad>(point3(min.x(), max.y(), max.z()), dx, -dz, mat)); // top
    sides.add(std::make_shared<quad>(point3(min.x(), min.y(), min.z()), dx, dz, mat));  // bottom

    bbox = Boxes(min, max);
}

bool Cube::hit(const ray& r, interval ray_t, hit_record& rec) const {
    return sides.hit(r, ray_t, rec);
}

Boxes Cube::bounding_box() const {
    return bbox;
}
