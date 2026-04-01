/*
** EPITECH PROJECT, 2024
** rebelotte
** File description:
** texture
*/
#include "texture.hpp"

// Solid colors Constructors
solid_color::solid_color(const color& albedo) : albedo(albedo) {}
solid_color::solid_color(double red, double green, double blue) : solid_color(color(red,green,blue)) {}

color solid_color::value(double u, double v, const point3& p) const {
    (void)u;
    (void)v;
    (void)p;
    return albedo;
}

// Checker Constructors
checker_texture::checker_texture(double scale, std::shared_ptr<texture> even, std::shared_ptr<texture> odd) : inv_scale(1.0 / scale), even(even), odd(odd) {}
checker_texture::checker_texture(double scale, const color& c1, const color& c2) : inv_scale(1.0 / scale), even(std::make_shared<solid_color>(c1)), odd(std::make_shared<solid_color>(c2)) {}

color checker_texture::value(double u, double v, const point3 &p) const {
    int xInteger = int(std::floor(inv_scale * p.x()));
    int yInteger = int(std::floor(inv_scale * p.y()));
    int zInteger = int(std::floor(inv_scale * p.z()));

    bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

    return isEven ? even->value(u, v, p) : odd->value(u, v, p);
}

// Perlin noise Constructors
noise_texture::noise_texture() {}
noise_texture::noise_texture(double scale) : scale(scale) {}

color noise_texture::value(double u, double v, const point3& p) const {
    (void)u;
    (void)v;
    (void)p;
    // return color(1,1,1) * 0.5 * (1.0 + noise.noise(scale * p)); //! Sans turbulence, ne pas retirer
    //return color(1,1,1) * noise.turb(p, 7); //! Avec turbulence
    return color(.5, .5, .5) * (1 + sin(scale * p.z() + 10 * noise.turb(p, 7))); //! Turbulence + scaling
}

// Image texture
image_texture::image_texture(const std::string& filename)
{
    loaded = image.loadFromFile(filename);
    if (loaded) {
        img_width  = image.getSize().x;
        img_height = image.getSize().y;
    } else {
        std::cerr << "image_texture: could not load " << filename << "\n";
    }
}

color image_texture::value(double u, double v, const point3& p) const
{
    (void)p;
    if (!loaded || img_width == 0 || img_height == 0)
        return color(1, 0, 1); // magenta = missing texture

    u = std::fmod(u, 1.0); if (u < 0) u += 1.0;
    v = std::fmod(v, 1.0); if (v < 0) v += 1.0;
    v = 1.0 - v; // flip vertically (image origin is top-left)

    unsigned int px = static_cast<unsigned int>(u * img_width);
    unsigned int py = static_cast<unsigned int>(v * img_height);
    if (px >= img_width)  px = img_width  - 1;
    if (py >= img_height) py = img_height - 1;

    sf::Color c = image.getPixel(px, py);
    static const double scale = 1.0 / 255.0;
    return color(c.r * scale, c.g * scale, c.b * scale);
}
