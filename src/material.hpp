/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** material
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include "utility.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "hittable.hpp"
#include "texture.hpp"
#include "pdf.hpp"

class hit_record;

/**
 * @brief Represents information about how a ray scatters when it hits a surface.
 */
class scatter_record {
public:
    color attenuation; /**< The attenuation of the scattered ray. */
    std::shared_ptr<pdf> pdf_ptr; /**< The probability density function associated with the scatter. */
    bool skip_pdf; /**< Indicates if the scatter should skip the PDF calculation. */
    ray skip_pdf_ray; /**< The ray used to skip the PDF calculation. */
};

/**
 * @brief Represents a material used for shading surfaces.
 */
class material {
public:
    virtual ~material() = default;

    /**
     * @brief Computes the emitted color of the material.
     * @param r_in The incident ray.
     * @param rec The hit record.
     * @param u The u texture coordinate.
     * @param v The v texture coordinate.
     * @param p The hit point.
     * @return The emitted color.
     */
    virtual color emitted(const ray& r_in, const hit_record& rec, double u, double v, const point3& p) const;

    /**
     * @brief Computes the scattered ray and attenuation for a given incident ray and hit record.
     * @param r_in The incident ray.
     * @param rec The hit record.
     * @param srec The scatter record to update.
     * @return True if scattering occurs, false otherwise.
     */
    virtual bool scatter(const ray& r_in, const hit_record& rec, scatter_record& srec) const;

    /**
     * @brief Computes the probability density function value associated with scattering.
     * @param r_in The incident ray.
     * @param rec The hit record.
     * @param scattered The scattered ray.
     * @return The probability density function value.
     */
    virtual double scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const;
};

/**
 * @brief Represents a Lambertian material for diffuse reflection.
 */
class lambertian : public material {
public:
    /**
     * @brief Constructs a Lambertian material with a specified albedo color.
     * @param albedo The albedo color.
     */
    lambertian(const color& albedo);

    /**
     * @brief Constructs a Lambertian material with a texture.
     * @param tex The texture.
     */
    lambertian(std::shared_ptr<texture> tex);

    bool scatter(const ray& r_in, const hit_record& rec, scatter_record& srec) const override;

    double scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const override;

private:
    std::shared_ptr<texture> tex; /**< The texture of the Lambertian material. */
};

/**
 * @brief Represents a metal material for specular reflection.
 */
class metal : public material {
public:
    /**
     * @brief Constructs a metal material with a specified albedo color and fuzziness.
     * @param albedo The albedo color.
     * @param fuzz The fuzziness factor (0 for no fuzziness).
     */
    metal(const color& albedo, double fuzz);

    bool scatter(const ray& r_in, const hit_record& rec, scatter_record& srec) const override;

private:
    color albedo; /**< The albedo color of the metal material. */
    double fuzz; /**< The fuzziness factor of the metal material. */
};

/**
 * @brief Represents a dielectric material for refraction and reflection.
 */
class dielectric : public material {
public:
    /**
     * @brief Constructs a dielectric material with a specified refraction index.
     * @param refraction_index The refraction index.
     */
    dielectric(double refraction_index);

    bool scatter(const ray& r_in, const hit_record& rec, scatter_record& srec) const override;

private:
    double refraction_index; /**< The refraction index of the dielectric material. */

    /**
     * @brief Computes the reflectance for a given cosine and refraction index.
     * @param cosine The cosine of the angle.
     * @param refraction_index The refraction index.
     * @return The reflectance.
     */
    static double reflectance(double cosine, double refraction_index);
};

/**
 * @brief Represents a diffuse light material for emitting light.
 */
class diffuse_light : public material {
public:
    /**
     * @brief Constructs a diffuse light material with a specified texture.
     * @param tex The texture.
     */
    diffuse_light(std::shared_ptr<texture> tex);

    /**
     * @brief Constructs a diffuse light material with a specified emission color.
     * @param emit The emission color.
     */
    diffuse_light(const color& emit);

    color emitted(const ray& r_in, const hit_record& rec, double u, double v, const point3& p) const override;

private:
    std::shared_ptr<texture> tex; /**< The texture of the diffuse light material. */
};

#endif
