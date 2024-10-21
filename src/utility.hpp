/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** utility
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <limits>
#include <memory>

const double infinity = std::numeric_limits<double>::infinity(); /**< Represents positive infinity. */
const double pi = 3.1415926535897932385; /**< The mathematical constant pi. */

// Utility Functions, used to compute random numbers for my vec3 class

/**
 * @brief Utility class for generating random numbers and converting between degrees and radians.
 */
class Random {
public:
    /**
     * @brief Converts degrees to radians.
     * 
     * @param degrees The angle in degrees.
     * @return The angle in radians.
     */
    static double degrees_to_radians(double degrees);

    /**
     * @brief Generates a random double between 0 and 1.
     * 
     * @return The random double.
     */
    static double random_double();

    /**
     * @brief Generates a random double between the given min and max values.
     * 
     * @param min The minimum value.
     * @param max The maximum value.
     * @return The random double.
     */
    static double random_double(double min, double max);

    /**
     * @brief Generates a random integer between the given min and max values.
     * 
     * @param min The minimum value.
     * @param max The maximum value.
     * @return The random integer.
     */
    static int random_int(int min, int max);
};

#endif /*! UTILITY_H */
