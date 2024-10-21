#include "vec3.hpp"

// Definition of vec3 methods
vec3::vec3() : e{0, 0, 0} {}
vec3::vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
vec3::vec3(double e0) : e{e0, e0, e0} {}

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }
double vec3::operator[](int i) const { return e[i]; }
double& vec3::operator[](int i) { return e[i]; }

vec3& vec3::operator+=(const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator*=(double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vec3& vec3::operator/=(double t) {
    return *this *= 1/t;
}

double vec3::length() const {
    return sqrt(length_squared());
}

double vec3::length_squared() const {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

bool vec3::near_zero() const {
    double s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

vec3 vec3::random() {
    return vec3(Random::random_double(), Random::random_double(), Random::random_double());
}

vec3 vec3::random(double min, double max) {
    return vec3(Random::random_double(min,max), Random::random_double(min,max), Random::random_double(min,max));
}

vec3 vec3::normalized() const {
    double len = length();
    return vec3(e[0] / len, e[1] / len, e[2] / len);
}

double vec3::dot(const vec3 &v) const {
    return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
}

vec3 vec3::cross(const vec3 &v) const {
    return vec3(e[1] * v.e[2] - e[2] * v.e[1],
                e[2] * v.e[0] - e[0] * v.e[2],
                e[0] * v.e[1] - e[1] * v.e[0]);
}

// Definition of Vec3Utils methods
std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

vec3 operator*(const vec3& v, double t) {
    return t * v;
}

vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

vec3 Vec3Utils::unit_vector(vec3 v) {
    return v / v.length();
}

vec3 Vec3Utils::random_in_unit_disk() {
    while (true) {
        vec3 p = vec3(Random::random_double(-1, 1), Random::random_double(-1, 1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

vec3 Vec3Utils::random_in_unit_sphere()
{
    while (true) {
        vec3 p = vec3::random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
}

vec3 Vec3Utils::random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 Vec3Utils::random_on_hemisphere(const vec3 &normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (on_unit_sphere.dot(normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

vec3 Vec3Utils::random_cosine_direction() {
    double r1 = Random::random_double();
    double r2 = Random::random_double();

    double phi = 2 * pi * r1;
    double x = cos(phi) * sqrt(r2);
    double y = sin(phi) * sqrt(r2);
    double z = sqrt(1 - r2);

    return vec3(x, y, z);
}

vec3 Vec3Utils::reflect(const vec3 &v, const vec3 &n) {
    return v - 2 * v.dot(n) * n;
}

vec3 Vec3Utils::refract(const vec3 &uv, const vec3 &n, double etai_over_etat) {
    double cos_theta = fmin((-uv).dot(n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -std::sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

// Definition of point3 methods
point3::point3() : vec3() {}
point3::point3(double x, double y, double z) : vec3(x, y, z) {}
point3::point3(double xyz) : vec3(xyz, xyz, xyz) {}

point3 &point3::operator=(const vec3 &other) {
    vec3::operator=(other);
    return *this;
}

point3 point3::operator+(const vec3 &other) const {
    return point3(e[0] + other.e[0], e[1] + other.e[1], e[2] + other.e[2]);
}

point3 point3::operator-(const vec3 &other) const {
    return point3(e[0] - other.e[0], e[1] - other.e[1], e[2] - other.e[2]);
}

vec3 point3::unit() const {
    double len = length();
    return vec3(e[0] / len, e[1] / len, e[2] / len);
}
bool operator<(const vec3 &vec, const vec3 &vec2)
{
    if (vec.length() > vec2.length()) {
        return true;   
    }
    return false;
    
}

bool operator||(const vec3 &vec, const vec3 &vec2)
{
    double x = vec.x() /vec2.x();
    double y = vec.y() /vec2.y();
    double z = vec.z() /vec2.z();

    if (x == y && y == z) {
        return true;   
    }
    return false;
    
}
