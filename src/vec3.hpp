/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** vec3
*/

#ifndef VEC3_H
#define VEC3_H

#include "utility.hpp"

/**
 * @brief A class representing a 3D vector.
 */
class vec3 {
public:
    double e[3]; /**< The components of the vector. */

    /**
     * @brief Default constructor. Initializes all components to zero.
     */
    vec3();

    /**
     * @brief Constructs a vector with the given components.
     * 
     * @param e0 The x-component.
     * @param e1 The y-component.
     * @param e2 The z-component.
     */
    vec3(double e0, double e1, double e2);

    /**
     * @brief Constructs a vector with all components set to the same value.
     * 
     * @param e0 The value for all components.
     */
    vec3(double e0);

    /**
     * @brief Returns the x-component of the vector.
     * 
     * @return The x-component.
     */
    double x() const;

    /**
     * @brief Returns the y-component of the vector.
     * 
     * @return The y-component.
     */
    double y() const;

    /**
     * @brief Returns the z-component of the vector.
     * 
     * @return The z-component.
     */
    double z() const;

    /**
     * @brief Negates the vector.
     * 
     * @return The negated vector.
     */
    vec3 operator-() const;

    /**
     * @brief Returns the value of the vector component at the specified index.
     * 
     * @param i The index of the component.
     * @return The value of the component.
     */
    double operator[](int i) const;

    /**
     * @brief Returns a reference to the vector component at the specified index.
     * 
     * @param i The index of the component.
     * @return A reference to the component.
     */
    double& operator[](int i);

    /**
     * @brief Adds a vector to this vector.
     * 
     * @param v The vector to add.
     * @return A reference to this vector after addition.
     */
    vec3& operator+=(const vec3& v);

    /**
     * @brief Multiplies this vector by a scalar.
     * 
     * @param t The scalar value.
     * @return A reference to this vector after multiplication.
     */
    vec3& operator*=(double t);

    /**
     * @brief Divides this vector by a scalar.
     * 
     * @param t The scalar value.
     * @return A reference to this vector after division.
     */
    vec3& operator/=(double t);

    /**
     * @brief Computes the length of the vector.
     * 
     * @return The length of the vector.
     */
    double length() const;

    /**
     * @brief Computes the squared length of the vector.
     * 
     * @return The squared length of the vector.
     */
    double length_squared() const;

    /**
     * @brief Checks if the vector is near zero.
     * 
     * @return True if the vector is near zero, false otherwise.
     */
    bool near_zero() const;

    /**
     * @brief Generates a random vector.
     * 
     * @return The random vector.
     */
    static vec3 random();

    /**
     * @brief Generates a random vector with components in the range [min, max].
     * 
     * @param min The minimum value.
     * @param max The maximum value.
     * @return The random vector.
     */
    static vec3 random(double min, double max);

    /**
     * @brief Returns the normalized version of the vector.
     * 
     * @return The normalized vector.
     */
    vec3 normalized() const;

    /**
     * @brief Computes the dot product of this vector with another vector.
     * 
     * @param v The other vector.
     * @return The dot product.
     */
    double dot(const vec3 &v) const;

    /**
     * @brief Computes the cross product of this vector with another vector.
     * 
     * @param v The other vector.
     * @return The cross product.
     */
    vec3 cross(const vec3 &v) const;
};

// Vector overload operator
std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(double t, const vec3& v);
vec3 operator*(const vec3& v, double t);
vec3 operator/(const vec3& v, double t);
bool operator<(const vec3 &vec, const vec3 &vec2);
bool operator||(const vec3 &vec, const vec3 &vec2);

/**
 * @brief A utility class for vector functions.
 */
class Vec3Utils : public vec3 {
public:
    /**
     * @brief Returns the unit vector in the direction of the given vector.
     * 
     * @param v The input vector.
     * @return The unit vector.
     */
    static vec3 unit_vector(vec3 v);

    /**
     * @brief Generates a random vector in the unit disk.
     * 
     * @return The random vector.
     */
    static vec3 random_in_unit_disk();

    /**
     * @brief Generates a random vector in the unit sphere.
     * 
     * @return The random vector.
     */
    static vec3 random_in_unit_sphere();

    /**
     * @brief Generates a random unit vector.
     * 
     * @return The random unit vector.
     */
    static vec3 random_unit_vector();

    /**
     * @brief Generates a random vector on the hemisphere with the given normal.
     * 
     * @param normal The normal vector.
     * @return The random vector.
     */
    static vec3 random_on_hemisphere(const vec3 &normal);

    /**
     * @brief Generates a random cosine-weighted direction.
     * 
     * @return The random direction.
     */
    static vec3 random_cosine_direction();

    /**
     * @brief Reflects the given vector around the given normal vector.
     * 
     * @param v The vector to reflect.
     * @param n The normal vector.
     * @return The reflected vector.
     */
    static vec3 reflect(const vec3 &v, const vec3 &n);

    /**
     * @brief Refracts the given vector based on the given normal vector and refraction ratio.
     * 
     * @param uv The incident vector.
     * @param n The normal vector.
     * @param etai_over_etat The ratio of the refractive indices.
     * @return The refracted vector.
     */
    static vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat);
};

/**
 * @brief A class representing a 3D point.
 */
class point3 : public vec3 {
public:
    /**
     * @brief Default constructor. Initializes all components to zero.
     */
    point3();

    /**
     * @brief Constructs a point with the given coordinates.
     * 
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param z The z-coordinate.
     */
    point3(double x, double y, double z);

    /**
     * @brief Constructs a point with all coordinates set to the same value.
     * 
     * @param xyz The value for all coordinates.
     */
    point3(double xyz);

    /**
     * @brief Assignment operator for a point from a vector.
     * 
     * @param other The vector to assign from.
     * @return A reference to this point after assignment.
     */
    point3 &operator=(const vec3 &other);

    /**
     * @brief Adds a vector to this point.
     * 
     * @param other The vector to add.
     * @return The resulting point.
     */
    point3 operator+(const vec3 &other) const;

    /**
     * @brief Subtracts a vector from this point.
     * 
     * @param other The vector to subtract.
     * @return The resulting point.
     */
    point3 operator-(const vec3 &other) const;

    /**
     * @brief Computes the unit vector of this point.
     * 
     * @return The unit vector.
     */
    vec3 unit() const;
};

#endif // VEC3_H
