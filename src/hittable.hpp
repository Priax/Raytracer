/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** hittable
*/

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include "interval.hpp"
#include "boxes.hpp"
#include <memory>

class material;

/**
 * @brief Structure utilitaire pour les matrices de transformation 4x4
 */
struct mat4 {
    double m[4][4];

    mat4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }

    mat4 operator*(const mat4& other) const {
        mat4 res;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                res.m[i][j] = m[i][0] * other.m[0][j] + m[i][1] * other.m[1][j] +
                              m[i][2] * other.m[2][j] + m[i][3] * other.m[3][j];
            }
        }
        return res;
    }

    point3 mult_point(const point3& p) const {
        return point3(
            m[0][0] * p.x() + m[0][1] * p.y() + m[0][2] * p.z() + m[0][3],
            m[1][0] * p.x() + m[1][1] * p.y() + m[1][2] * p.z() + m[1][3],
            m[2][0] * p.x() + m[2][1] * p.y() + m[2][2] * p.z() + m[2][3]
        );
    }

    vec3 mult_dir(const vec3& v) const {
        return vec3(
            m[0][0] * v.x() + m[0][1] * v.y() + m[0][2] * v.z(),
            m[1][0] * v.x() + m[1][1] * v.y() + m[1][2] * v.z(),
            m[2][0] * v.x() + m[2][1] * v.y() + m[2][2] * v.z()
        );
    }

    mat4 transpose() const {
        mat4 res;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                res.m[i][j] = m[j][i];
        return res;
    }

    mat4 inverse() const;
};

/**
 * @brief Represents information about a hit point.
 */
class hit_record {
public:
    point3 p; /**< The hit point. */
    vec3 normal; /**< The normal at the hit point. */
    const material *mat; /**< The material of the hit object. */
    double t; /**< The parameter 't' of the ray at the hit point. */
    double u; /**< The u texture coordinate. */
    double v; /**< The v texture coordinate. */
    bool front_face; /**< Indicates if the ray hit the front face of the object. */

    void set_face_normal(const ray& r, const vec3& outward_normal);
};

/**
 * @brief Represents a hittable object in the scene.
 */
class hittable {
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
    virtual Boxes bounding_box() const = 0;
    virtual double pdf_value(const point3& origin, const vec3& direction) const;
    virtual vec3 random(const point3& origin) const;
};

class translate : public hittable {
public:
    translate(std::shared_ptr<hittable> object, const vec3& offset);
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;
private:
    std::shared_ptr<hittable> object;
    vec3 offset;
    Boxes bbox;
};

class rotate_y : public hittable {
public:
    rotate_y(std::shared_ptr<hittable> object, double angle);
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;
private:
    std::shared_ptr<hittable> object;
    double sin_theta;
    double cos_theta;
    Boxes bbox;
};

class rotate_x : public hittable {
public:
    rotate_x(std::shared_ptr<hittable> object, double angle);
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override;
    Boxes bounding_box() const override;
private:
    std::shared_ptr<hittable> object;
    double sin_theta;
    double cos_theta;
    Boxes bbox;
};

class rotate_z : public hittable {
public:
    rotate_z(std::shared_ptr<hittable> object, double angle);
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override;
    Boxes bounding_box() const override;
private:
    std::shared_ptr<hittable> object;
    double sin_theta;
    double cos_theta;
    Boxes bbox;
};

class shear : public hittable {
public:
    shear(std::shared_ptr<hittable> object, double hxy, double hxz, double hyx, double hyz, double hzx, double hzy);
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;
private:
    std::shared_ptr<hittable> object;
    Boxes bbox;
    double m[3][3];
    double inv[3][3];
    double invT[3][3];
    vec3 multiply_matrix(const vec3& v, const double mat[3][3]) const;
};

/**
 * @brief Un Noeud de graphe de scène capable d'appliquer n'importe quelle
 * combinaison de translation, rotation, scale et shear via une matrice 4x4.
 */
class TransformNode : public hittable {
public:
    /**
     * @param obj L'objet à transformer
     * @param transform_matrix La matrice 4x4 finale représentant la transformation
     */
    TransformNode(std::shared_ptr<hittable> obj, const mat4& transform_matrix);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
    Boxes bounding_box() const override;

private:
    std::shared_ptr<hittable> object;
    mat4 M;       // Matrice Espace Objet -> Monde
    mat4 Minv;    // Matrice Espace Monde -> Objet
    mat4 MinvT;   // Transposée de l'inverse (Pour les normales)
    Boxes bbox;
};

#endif
