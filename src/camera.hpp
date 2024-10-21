/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** camera
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.hpp"
#include "color.hpp"
#include "vec3.hpp"
#include "material.hpp"
#include "pdf.hpp"

/**
 * @brief Represents a camera used for rendering scenes.
 */
class camera {
public:
    int image_height = 100; /**< The height of the rendered image. */
    int image_width = 100; /**< The width of the rendered image. */
    int samples_per_pixel = 10; /**< Number of samples per pixel. More samples reduce noise. */
    int max_depth = 10; /**< Maximum number of ray bounces in the scene. */
    int ambient_multiplier = 1.0; /**< Ambient light multiplier. */
    color background; /**< Background color of the raytracer. */

    double vfov = 90; /**< Vertical field of view (in degrees). */
    point3 lookfrom = point3(0, 0, 0); /**< Position of the camera. */
    point3 lookat   = point3(0, 0, -1); /**< Point the camera is looking at. */
    vec3 vup      = vec3(0, 1, 0); /**< Up direction relative to the camera. */

    double defocus_angle = 0; /**< Defocus angle for depth of field effect. */
    double focus_dist = 10; /**< Focus distance for depth of field effect. */

    std::shared_ptr<std::list<sf::Color>> _colorsQueue = nullptr; /* Initialize list of colors */
    std::shared_ptr<std::mutex> _colorsQueueMutex = std::make_shared<std::mutex>(); /* Queue of color data */

    /**
     * @brief Renders the scene using the provided world and lights.
     * @param world The hittable representing the scene geometry.
     * @param lights The hittable representing the light sources in the scene.
     */
    void render(const hittable& world, const hittable &lights);

private:
    double pixel_samples_scale; /**< Scale factor for pixel samples. */
    point3 center; /**< Center of the camera. */
    point3 pixel00_loc; /**< Location of the pixel (0,0) in world space. */
    vec3 pixel_delta_u; /**< Pixel delta along the u direction. */
    vec3 pixel_delta_v; /**< Pixel delta along the v direction. */
    vec3 u, v, w; /**< Camera coordinate system axes. */
    vec3 defocus_disk_u; /**< Direction of defocus disk along u axis. */
    vec3 defocus_disk_v; /**< Direction of defocus disk along v axis. */
    int sqrt_spp; /**< Square root of samples per pixel. */
    double recip_sqrt_spp; /**< Reciprocal of the square root of samples per pixel. */

    void initialize(); /**< Initializes camera parameters. */
    ray get_ray(int i, int j, int s_i, int s_j) const; /**< Gets a ray for a given pixel and sample. */
    vec3 sample_square() const; /**< Samples a square for antialiasing. */
    point3 defocus_disk_sample() const; /**< Samples the defocus disk for depth of field effect. */
    color ray_color(const ray &r, int depth, const hittable &world, const hittable &lights) const; /**< Computes color for a given ray. */
    vec3 sample_square_stratified(int s_i, int s_j) const; /**< Stratified sampling for antialiasing. */
};

#endif
