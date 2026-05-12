/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** hittable
*/

#include "hittable.hpp"
#include <cmath>

mat4 mat4::inverse() const {
    double inv[16], det;
    const double* m_ptr = &m[0][0];
    mat4 res;

    inv[0] = m_ptr[5]  * m_ptr[10] * m_ptr[15] - 
             m_ptr[5]  * m_ptr[11] * m_ptr[14] - 
             m_ptr[9]  * m_ptr[6]  * m_ptr[15] + 
             m_ptr[9]  * m_ptr[7]  * m_ptr[14] +
             m_ptr[13] * m_ptr[6]  * m_ptr[11] - 
             m_ptr[13] * m_ptr[7]  * m_ptr[10];

    inv[4] = -m_ptr[4]  * m_ptr[10] * m_ptr[15] + 
              m_ptr[4]  * m_ptr[11] * m_ptr[14] + 
              m_ptr[8]  * m_ptr[6]  * m_ptr[15] - 
              m_ptr[8]  * m_ptr[7]  * m_ptr[14] - 
              m_ptr[12] * m_ptr[6]  * m_ptr[11] + 
              m_ptr[12] * m_ptr[7]  * m_ptr[10];

    inv[8] = m_ptr[4]  * m_ptr[9] * m_ptr[15] - 
             m_ptr[4]  * m_ptr[11] * m_ptr[13] - 
             m_ptr[8]  * m_ptr[5] * m_ptr[15] + 
             m_ptr[8]  * m_ptr[7] * m_ptr[13] + 
             m_ptr[12] * m_ptr[5] * m_ptr[11] - 
             m_ptr[12] * m_ptr[7] * m_ptr[9];

    inv[12] = -m_ptr[4]  * m_ptr[9] * m_ptr[14] + 
               m_ptr[4]  * m_ptr[10] * m_ptr[13] +
               m_ptr[8]  * m_ptr[5] * m_ptr[14] - 
               m_ptr[8]  * m_ptr[6] * m_ptr[13] - 
               m_ptr[12] * m_ptr[5] * m_ptr[10] + 
               m_ptr[12] * m_ptr[6] * m_ptr[9];

    inv[1] = -m_ptr[1]  * m_ptr[10] * m_ptr[15] + 
              m_ptr[1]  * m_ptr[11] * m_ptr[14] + 
              m_ptr[9]  * m_ptr[2] * m_ptr[15] - 
              m_ptr[9]  * m_ptr[3] * m_ptr[14] - 
              m_ptr[13] * m_ptr[2] * m_ptr[11] + 
              m_ptr[13] * m_ptr[3] * m_ptr[10];

    inv[5] = m_ptr[0]  * m_ptr[10] * m_ptr[15] - 
             m_ptr[0]  * m_ptr[11] * m_ptr[14] - 
             m_ptr[8]  * m_ptr[2] * m_ptr[15] + 
             m_ptr[8]  * m_ptr[3] * m_ptr[14] + 
             m_ptr[12] * m_ptr[2] * m_ptr[11] - 
             m_ptr[12] * m_ptr[3] * m_ptr[10];

    inv[9] = -m_ptr[0]  * m_ptr[9] * m_ptr[15] + 
              m_ptr[0]  * m_ptr[11] * m_ptr[13] + 
              m_ptr[8]  * m_ptr[1] * m_ptr[15] - 
              m_ptr[8]  * m_ptr[3] * m_ptr[13] - 
              m_ptr[12] * m_ptr[1] * m_ptr[11] + 
              m_ptr[12] * m_ptr[3] * m_ptr[9];

    inv[13] = m_ptr[0]  * m_ptr[9] * m_ptr[14] - 
              m_ptr[0]  * m_ptr[10] * m_ptr[13] - 
              m_ptr[8]  * m_ptr[1] * m_ptr[14] + 
              m_ptr[8]  * m_ptr[2] * m_ptr[13] + 
              m_ptr[12] * m_ptr[1] * m_ptr[10] - 
              m_ptr[12] * m_ptr[2] * m_ptr[9];

    inv[2] = m_ptr[1]  * m_ptr[6] * m_ptr[15] - 
             m_ptr[1]  * m_ptr[7] * m_ptr[14] - 
             m_ptr[5]  * m_ptr[2] * m_ptr[15] + 
             m_ptr[5]  * m_ptr[3] * m_ptr[14] + 
             m_ptr[13] * m_ptr[2] * m_ptr[7] - 
             m_ptr[13] * m_ptr[3] * m_ptr[6];

    inv[6] = -m_ptr[0]  * m_ptr[6] * m_ptr[15] + 
              m_ptr[0]  * m_ptr[7] * m_ptr[14] + 
              m_ptr[4]  * m_ptr[2] * m_ptr[15] - 
              m_ptr[4]  * m_ptr[3] * m_ptr[14] - 
              m_ptr[12] * m_ptr[2] * m_ptr[7] + 
              m_ptr[12] * m_ptr[3] * m_ptr[6];

    inv[10] = m_ptr[0]  * m_ptr[5] * m_ptr[15] - 
              m_ptr[0]  * m_ptr[7] * m_ptr[13] - 
              m_ptr[4]  * m_ptr[1] * m_ptr[15] + 
              m_ptr[4]  * m_ptr[3] * m_ptr[13] + 
              m_ptr[12] * m_ptr[1] * m_ptr[7] - 
              m_ptr[12] * m_ptr[3] * m_ptr[5];

    inv[14] = -m_ptr[0]  * m_ptr[5] * m_ptr[14] + 
               m_ptr[0]  * m_ptr[6] * m_ptr[13] + 
               m_ptr[4]  * m_ptr[1] * m_ptr[14] - 
               m_ptr[4]  * m_ptr[2] * m_ptr[13] - 
               m_ptr[12] * m_ptr[1] * m_ptr[6] + 
               m_ptr[12] * m_ptr[2] * m_ptr[5];

    inv[3] = -m_ptr[1] * m_ptr[6] * m_ptr[11] + 
              m_ptr[1] * m_ptr[7] * m_ptr[10] + 
              m_ptr[5] * m_ptr[2] * m_ptr[11] - 
              m_ptr[5] * m_ptr[3] * m_ptr[10] - 
              m_ptr[9] * m_ptr[2] * m_ptr[7] + 
              m_ptr[9] * m_ptr[3] * m_ptr[6];

    inv[7] = m_ptr[0] * m_ptr[6] * m_ptr[11] - 
             m_ptr[0] * m_ptr[7] * m_ptr[10] - 
             m_ptr[4] * m_ptr[2] * m_ptr[11] + 
             m_ptr[4] * m_ptr[3] * m_ptr[10] + 
             m_ptr[8] * m_ptr[2] * m_ptr[7] - 
             m_ptr[8] * m_ptr[3] * m_ptr[6];

    inv[11] = -m_ptr[0] * m_ptr[5] * m_ptr[11] + 
               m_ptr[0] * m_ptr[7] * m_ptr[9] + 
               m_ptr[4] * m_ptr[1] * m_ptr[11] - 
               m_ptr[4] * m_ptr[3] * m_ptr[9] - 
               m_ptr[8] * m_ptr[1] * m_ptr[7] + 
               m_ptr[8] * m_ptr[3] * m_ptr[5];

    inv[15] = m_ptr[0] * m_ptr[5] * m_ptr[10] - 
              m_ptr[0] * m_ptr[6] * m_ptr[9] - 
              m_ptr[4] * m_ptr[1] * m_ptr[10] + 
              m_ptr[4] * m_ptr[2] * m_ptr[9] + 
              m_ptr[8] * m_ptr[1] * m_ptr[6] - 
              m_ptr[8] * m_ptr[2] * m_ptr[5];

    det = m_ptr[0] * inv[0] + m_ptr[1] * inv[4] + m_ptr[2] * inv[8] + m_ptr[3] * inv[12];

    if (det == 0) return res;

    det = 1.0 / det;
    for (int i = 0; i < 16; i++) {
        res.m[i / 4][i % 4] = inv[i] * det;
    }
    return res;
}

double hittable::pdf_value(const point3& origin, const vec3& direction) const {
    (void)origin;
    (void)direction;
    return 0.0;
}

vec3 hittable::random(const point3 &origin) const {
    (void)origin;
    return vec3(1, 0, 0);
}

void hit_record::set_face_normal(const ray &r, const vec3& outward_normal) {
    front_face = r.direction().dot(outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}

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

    if (!object->hit(rotated_r, ray_t, rec))
        return false;

    point3 p = rec.p;
    p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
    p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

    vec3 normal = rec.normal;
    normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.normal = normal;

    return true;
}

Boxes rotate_y::bounding_box() const { return bbox; }

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

    origin[1] = cos_theta * r.origin()[1] + sin_theta * r.origin()[2];
    origin[2] = -sin_theta * r.origin()[1] + cos_theta * r.origin()[2];

    direction[1] = cos_theta * r.direction()[1] + sin_theta * r.direction()[2];
    direction[2] = -sin_theta * r.direction()[1] + cos_theta * r.direction()[2];

    ray rotated_r(origin, direction, r.time());

    if (!object->hit(rotated_r, ray_t, rec))
        return false;

    point3 p = rec.p;
    p[1] = cos_theta * rec.p[1] - sin_theta * rec.p[2];
    p[2] = sin_theta * rec.p[1] + cos_theta * rec.p[2];

    vec3 normal = rec.normal;
    normal[1] = cos_theta * rec.normal[1] - sin_theta * rec.normal[2];
    normal[2] = sin_theta * rec.normal[1] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.normal = normal;

    return true;
}

Boxes rotate_x::bounding_box() const { return bbox; }

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

    origin[0] = cos_theta * r.origin()[0] + sin_theta * r.origin()[1];
    origin[1] = -sin_theta * r.origin()[0] + cos_theta * r.origin()[1];

    direction[0] = cos_theta * r.direction()[0] + sin_theta * r.direction()[1];
    direction[1] = -sin_theta * r.direction()[0] + cos_theta * r.direction()[1];

    ray rotated_r(origin, direction, r.time());

    if (!object->hit(rotated_r, ray_t, rec))
        return false;

    point3 p = rec.p;
    p[0] = cos_theta * rec.p[0] - sin_theta * rec.p[1];
    p[1] = sin_theta * rec.p[0] + cos_theta * rec.p[1];

    vec3 normal = rec.normal;
    normal[0] = cos_theta * rec.normal[0] - sin_theta * rec.normal[1];
    normal[1] = sin_theta * rec.normal[0] + cos_theta * rec.normal[1];

    rec.p = p;
    rec.normal = normal;

    return true;
}

Boxes rotate_z::bounding_box() const { return bbox; }

shear::shear(std::shared_ptr<hittable> object, double hxy, double hxz, double hyx, double hyz, double hzx, double hzy) 
    : object(object) 
{
    m[0][0] = 1.0; m[0][1] = hxy; m[0][2] = hxz;
    m[1][0] = hyx; m[1][1] = 1.0; m[1][2] = hyz;
    m[2][0] = hzx; m[2][1] = hzy; m[2][2] = 1.0;

    double det = m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1])
               - m[0][1]*(m[1][0]*m[2][2] - m[1][2]*m[2][0])
               + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);

    if (det == 0.0) det = 1.0;

    inv[0][0] =  (m[1][1]*m[2][2] - m[1][2]*m[2][1]) / det;
    inv[0][1] = -(m[0][1]*m[2][2] - m[0][2]*m[2][1]) / det;
    inv[0][2] =  (m[0][1]*m[1][2] - m[0][2]*m[1][1]) / det;
    inv[1][0] = -(m[1][0]*m[2][2] - m[1][2]*m[2][0]) / det;
    inv[1][1] =  (m[0][0]*m[2][2] - m[0][2]*m[2][0]) / det;
    inv[1][2] = -(m[0][0]*m[1][2] - m[0][2]*m[1][0]) / det;
    inv[2][0] =  (m[1][0]*m[2][1] - m[1][1]*m[2][0]) / det;
    inv[2][1] = -(m[0][0]*m[2][1] - m[0][1]*m[2][0]) / det;
    inv[2][2] =  (m[0][0]*m[1][1] - m[0][1]*m[1][0]) / det;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            invT[i][j] = inv[j][i];

    bbox = object->bounding_box();
    point3 min(infinity, infinity, infinity);
    point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                double x = i * bbox.x.max + (1 - i) * bbox.x.min;
                double y = j * bbox.y.max + (1 - j) * bbox.y.min;
                double z = k * bbox.z.max + (1 - k) * bbox.z.min;
                vec3 tester = multiply_matrix(vec3(x, y, z), m);
                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }
    bbox = Boxes(min, max);
}

vec3 shear::multiply_matrix(const vec3& v, const double mat[3][3]) const {
    return vec3(
        mat[0][0]*v.x() + mat[0][1]*v.y() + mat[0][2]*v.z(),
        mat[1][0]*v.x() + mat[1][1]*v.y() + mat[1][2]*v.z(),
        mat[2][0]*v.x() + mat[2][1]*v.y() + mat[2][2]*v.z()
    );
}

bool shear::hit(const ray &r, interval ray_t, hit_record &rec) const {
    vec3 o_vec = multiply_matrix(r.origin(), inv);
    point3 origin(o_vec.x(), o_vec.y(), o_vec.z());
    vec3 direction = multiply_matrix(r.direction(), inv);
    ray sheared_r(origin, direction, r.time());

    if (!object->hit(sheared_r, ray_t, rec))
        return false;

    rec.p = multiply_matrix(rec.p, m);
    vec3 normal = multiply_matrix(rec.normal, invT);
    rec.normal = Vec3Utils::unit_vector(normal); 

    return true;
}

Boxes shear::bounding_box() const { return bbox; }

TransformNode::TransformNode(std::shared_ptr<hittable> obj, const mat4& transform_matrix) 
    : object(obj), M(transform_matrix) 
{
    Minv = M.inverse();
    MinvT = Minv.transpose();

    bbox = object->bounding_box();
    point3 min(infinity, infinity, infinity);
    point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                double x = i * bbox.x.max + (1 - i) * bbox.x.min;
                double y = j * bbox.y.max + (1 - j) * bbox.y.min;
                double z = k * bbox.z.max + (1 - k) * bbox.z.min;

                point3 tester = M.mult_point(point3(x, y, z));

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }
    bbox = Boxes(min, max);
}

bool TransformNode::hit(const ray& r, interval ray_t, hit_record& rec) const {
    point3 origin = Minv.mult_point(r.origin());
    vec3 direction = Minv.mult_dir(r.direction());
    ray object_ray(origin, direction, r.time());

    if (!object->hit(object_ray, ray_t, rec))
        return false;

    rec.p = M.mult_point(rec.p);

    vec3 normal = MinvT.mult_dir(rec.normal);
    rec.normal = Vec3Utils::unit_vector(normal);

    return true;
}

Boxes TransformNode::bounding_box() const { 
    return bbox; 
}
