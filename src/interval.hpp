/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** interval
*/

#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>
#include "utility.hpp"

/**
 * @brief Represents a closed interval [min, max].
 */
class interval {
public:
    double min; /**< The minimum value of the interval. */
    double max; /**< The maximum value of the interval. */

    /**
     * @brief Default constructor. Initializes the interval to an empty interval.
     */
    interval();

    /**
     * @brief Constructs an interval with specified minimum and maximum values.
     * @param min The minimum value of the interval.
     * @param max The maximum value of the interval.
     */
    interval(double min, double max);

    /**
     * @brief Constructs an interval that contains two other intervals.
     * @param a The first interval.
     * @param b The second interval.
     */
    interval(const interval& a, const interval& b);

    /**
     * @brief Computes the size of the interval.
     * @return The size of the interval.
     */
    double size() const;

    /**
     * @brief Checks if a value is contained within the interval.
     * @param x The value to check.
     * @return True if the value is contained within the interval, false otherwise.
     */
    bool contains(double x) const;

    /**
     * @brief Checks if the interval surrounds a value.
     * @param x The value to check.
     * @return True if the interval surrounds the value, false otherwise.
     */
    bool surrounds(double x) const;

    /**
     * @brief Clamps a value to the interval.
     * @param x The value to clamp.
     * @return The clamped value.
     */
    double clamp(double x) const;

    /**
     * @brief Expands the interval by a delta value.
     * @param delta The amount by which to expand the interval.
     * @return The expanded interval.
     */
    interval expand(double delta) const;

    static const interval empty, universe; /**< Static instances of an empty interval and the universe interval. */
};

/**
 * @brief Overloaded operator to translate an interval by a displacement.
 * @param ival The interval.
 * @param displacement The displacement value.
 * @return The translated interval.
 */
interval operator+(const interval& ival, double displacement);

/**
 * @brief Overloaded operator to translate an interval by a displacement.
 * @param displacement The displacement value.
 * @param ival The interval.
 * @return The translated interval.
 */
interval operator+(double displacement, const interval& ival);

#endif
