/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** pdf
*/

#ifndef PDF_HPP_
#define PDF_HPP_

#include "utility.hpp"
#include "hittable_list.hpp"
#include "ortho.hpp"

/**
 * @brief Abstract class representing a probability density function (PDF).
 */
class pdf {
public:
    /**
     * @brief Virtual destructor for the PDF class.
     */
    virtual ~pdf() {}

    /**
     * @brief Get the value of the PDF for a given direction.
     * 
     * @param direction The direction vector.
     * @return The value of the PDF.
     */
    virtual double value(const vec3& direction) const = 0;

    /**
     * @brief Generate a random direction based on the PDF.
     * 
     * @return The generated direction vector.
     */
    virtual vec3 generate() const = 0;
};

/**
 * @brief PDF for cosine-weighted scattering.
 */
class cosine_pdf : public pdf {
public:
    /**
     * @brief Construct a new cosine_pdf object.
     * 
     * @param w The w-axis vector.
     */
    cosine_pdf(const vec3& w);

    double value(const vec3& direction) const override;

    vec3 generate() const override;

private:
    OrthonormalFrame uvw; /**< Orthonormal frame for cosine-weighted scattering. */
};

/**
 * @brief PDF for sampling hittable objects.
 */
class hittable_pdf : public pdf {
public:
    /**
     * @brief Construct a new hittable_pdf object.
     * 
     * @param objects The hittable objects to sample from.
     * @param origin The origin point for sampling.
     */
    hittable_pdf(const hittable& objects, const point3& origin);

    double value(const vec3& direction) const override;

    vec3 generate() const override;

private:
    const hittable& objects; /**< Reference to the hittable objects to sample from. */
    point3 origin; /**< The origin point for sampling. */
};

/**
 * @brief Mixture PDF combining two other PDFs.
 */
class mixture_pdf : public pdf {
public:
    /**
     * @brief Construct a new mixture_pdf object.
     * 
     * @param p0 The first PDF.
     * @param p1 The second PDF.
     */
    mixture_pdf(std::shared_ptr<pdf> p0, std::shared_ptr<pdf> p1);

    double value(const vec3& direction) const override;

    vec3 generate() const override;

private:
    std::shared_ptr<pdf> p[2]; /**< Array of PDFs for mixture. */
};

#endif /* !PDF_HPP_ */
