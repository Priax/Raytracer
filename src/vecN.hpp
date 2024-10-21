/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** vecN
*/

#ifndef VEC_H
#define VEC_H

#include "utility.hpp"
#include <array>

/**
 * @brief A class template representing a vector of fixed size.
 * 
 * @tparam T The type of elements in the vector.
 * @tparam N The size of the vector.
 */
template<typename T, size_t N>
class VectorN {
public:
    std::array<T, N> e; /**< The elements of the vector. */

    /**
     * @brief Default constructor. Initializes all elements to zero.
     */
    VectorN();

    /**
     * @brief Constructs a vector with all elements set to the given value.
     * 
     * @param val The value to set for all elements.
     */
    explicit VectorN(const T& val);

    /**
     * @brief Constructs a vector from the given array.
     * 
     * @param arr The array containing elements of the vector.
     */
    VectorN(const std::array<T, N>& arr);

    /**
     * @brief Accesses the element at the specified index.
     * 
     * @param i The index of the element to access.
     * @return The value of the element.
     */
    T operator[](size_t i) const;

    /**
     * @brief Accesses the element at the specified index for modification.
     * 
     * @param i The index of the element to access.
     * @return A reference to the element.
     */
    T& operator[](size_t i);

    /**
     * @brief Adds another vector to this vector.
     * 
     * @param v The vector to add.
     * @return A reference to this vector after addition.
     */
    VectorN& operator+=(const VectorN& v);

    /**
     * @brief Subtracts another vector from this vector.
     * 
     * @param v The vector to subtract.
     * @return A reference to this vector after subtraction.
     */
    VectorN& operator-=(const VectorN& v);

    /**
     * @brief Multiplies this vector by a scalar.
     * 
     * @param t The scalar value.
     * @return A reference to this vector after multiplication.
     */
    VectorN& operator*=(const T& t);

    /**
     * @brief Divides this vector by a scalar.
     * 
     * @param t The scalar value.
     * @return A reference to this vector after division.
     */
    VectorN& operator/=(const T& t);

    /**
     * @brief Computes the length of the vector.
     * 
     * @return The length of the vector.
     */
    T length() const;

    /**
     * @brief Computes the squared length of the vector.
     * 
     * @return The squared length of the vector.
     */
    T length_squared() const;

    /**
     * @brief Checks if the vector is near zero.
     * 
     * @return True if the vector is near zero, false otherwise.
     */
    bool near_zero() const;

    /**
     * @brief Returns the normalized version of the vector.
     * 
     * @return The normalized vector.
     */
    VectorN normalized() const;

    /**
     * @brief Computes the dot product of this vector with another vector.
     * 
     * @param v The other vector.
     * @return The dot product.
     */
    T dot(const VectorN& v) const;

    /**
     * @brief Computes the cross product of this vector with another vector.
     * 
     * @param v The other vector.
     * @return The cross product.
     */
    VectorN cross(const VectorN& v) const;

    /**
     * @brief Generates a random vector.
     * 
     * @return The random vector.
     */
    static VectorN random();

    /**
     * @brief Generates a random vector with components in the range [min, max].
     * 
     * @param min The minimum value for the components.
     * @param max The maximum value for the components.
     * @return The random vector.
     */
    static VectorN random(T min, T max);
};

// Additional utility functions can be added here

#endif // VEC_H
