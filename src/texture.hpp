/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** texture
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include "utility.hpp"
#include "color.hpp"
#include "perlin.hpp"

/**
 * @brief Abstract base class for textures.
 */
class texture {
public:
    virtual ~texture() = default;

    /**
     * @brief Get the color value of the texture at given (u, v) coordinates and point p.
     * 
     * @param u The u-coordinate.
     * @param v The v-coordinate.
     * @param p The point in space.
     * @return The color value of the texture.
     */
    virtual color value(double u, double v, const point3& p) const = 0;
};

/**
 * @brief Texture representing a solid color.
 */
class solid_color : public texture {
public:
    /**
     * @brief Construct a solid color texture with given albedo color.
     * 
     * @param albedo The color of the texture.
     */
    solid_color(const color& albedo);

    /**
     * @brief Construct a solid color texture with given RGB values.
     * 
     * @param red The red component of the color.
     * @param green The green component of the color.
     * @param blue The blue component of the color.
     */
    solid_color(double red, double green, double blue);

    color value(double u, double v, const point3& p) const override;

private:
    color albedo; /**< The color of the texture. */
};

/**
 * @brief Texture representing a checker pattern.
 */
class checker_texture : public texture {
public:
    /**
     * @brief Construct a checker texture with given scale and two textures.
     * 
     * @param scale The scale of the checker pattern.
     * @param even The texture for even squares.
     * @param odd The texture for odd squares.
     */
    checker_texture(double scale, std::shared_ptr<texture> even, std::shared_ptr<texture> odd);

    /**
     * @brief Construct a checker texture with given scale and two colors.
     * 
     * @param scale The scale of the checker pattern.
     * @param c1 The color for even squares.
     * @param c2 The color for odd squares.
     */
    checker_texture(double scale, const color& c1, const color& c2);

    color value(double u, double v, const point3& p) const override;

private:
    double inv_scale; /**< Inverse scale of the checker pattern. */
    std::shared_ptr<texture> even; /**< Texture for even squares. */
    std::shared_ptr<texture> odd; /**< Texture for odd squares. */
};

/**
 * @brief Texture representing a noise pattern.
 */
class noise_texture : public texture {
public:
    /**
     * @brief Construct a noise texture with default scale.
     */
    noise_texture();

    /**
     * @brief Construct a noise texture with given scale.
     * 
     * @param scale The scale of the noise.
     */
    noise_texture(double scale);

    color value(double u, double v, const point3& p) const override;

private:
    perlin noise; /**< Perlin noise generator. */
    double scale; /**< Scale of the noise pattern. */
};

#endif
