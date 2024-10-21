/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** perlin
*/

#ifndef PERLIN_H
#define PERLIN_H

#include "utility.hpp"
#include "vec3.hpp"

/**
 * @brief Class for generating Perlin noise.
 */
class perlin {
public:
    /**
     * @brief Default constructor for Perlin noise.
     */
    perlin();

    /**
     * @brief Destructor for Perlin noise.
     */
    ~perlin();

    /**
     * @brief Compute Perlin noise at a given point.
     * 
     * @param p The point at which to compute Perlin noise.
     * @return The Perlin noise value.
     */
    double noise(const vec3& p) const;

    /**
     * @brief Compute Perlin turbulence at a given point.
     * 
     * @param p The point at which to compute Perlin turbulence.
     * @param depth The depth of the turbulence computation.
     * @return The Perlin turbulence value.
     */
    double turb(const point3& p, int depth) const;

private:
    static const int point_count = 256; /**< Number of points for Perlin noise. */
    vec3* randvec; /**< Random vectors for Perlin noise. */
    int *perm_x; /**< Permutation array for x-coordinate. */
    int *perm_y; /**< Permutation array for y-coordinate. */
    int *perm_z; /**< Permutation array for z-coordinate. */

    /**
     * @brief Generate a permutation array for Perlin noise.
     * 
     * @return The generated permutation array.
     */
    static int *perlin_generate_perm();

    /**
     * @brief Permute the elements of a permutation array.
     * 
     * @param p The permutation array to permute.
     * @param n The size of the permutation array.
     */
    static void permute(int *p, int n);

    /**
     * @brief Interpolate Perlin noise values.
     * 
     * @param c The gradient vectors.
     * @param u Interpolation parameter in the x-direction.
     * @param v Interpolation parameter in the y-direction.
     * @param w Interpolation parameter in the z-direction.
     * @return The interpolated Perlin noise value.
     */
    static double perlin_interp(const vec3 c[2][2][2], double u, double v, double w);
};

#endif
