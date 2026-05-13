/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** obj_loader
*/

#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "hittable_list.hpp"
#include "material.hpp"
#include <string>
#include <memory>

/**
 * @brief Loads a .obj file and returns a hittable_list of triangles.
 *
 * Supports: vertices (v), texture coordinates (vt), faces (f).
 * Face indices can be: v, v/vt, v//vn, v/vt/vn.
 * Polygons with more than 3 vertices are fan-triangulated.
 *
 * @param filename Path to the .obj file.
 * @param mat      Material to apply to all triangles.
 * @param scale    The factor to resize the loaded mesh.
 * @return hittable_list containing all triangles of the mesh.
 */
hittable_list loadOBJ(const std::string& filename, std::shared_ptr<material> mat, double scale = 1.0);

#endif
