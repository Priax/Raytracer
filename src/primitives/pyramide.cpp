/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** pyramide
*/
#include "pyramide.hpp"
#include "triangle.hpp"
pyramide::pyramide(const point3 summit,const point3 basis1,const point3 basis2, const point3 basis3, const point3 basis4, const std::shared_ptr<material> mat) : mat(mat)
{
    vec3 u = basis2 - basis1;
    vec3 v = basis3 - basis1;
    vec3 w = basis4 - basis1;
    point3 max = basis1;
    max.e[2] = summit.e[2];
    sides.add(std::make_shared<triangle>(summit, basis1, basis2, mat));
    sides.add(std::make_shared<triangle>(summit, basis2, basis3, mat));
    sides.add(std::make_shared<triangle>(summit, basis3, basis4, mat));
    sides.add(std::make_shared<triangle>(summit, basis4, basis1, mat));
    if (u < v && u < w) {
        sides.add(std::make_shared<quad>(basis1,v ,w, mat));
        max.e[0] += u.e[0];
        max.e[1] += u.e[1];
    } else if (v< u && v < w) {
        sides.add(std::make_shared<quad>(basis1,u ,w, mat));
        max.e[0] += v.e[0];
        max.e[1] += v.e[1];

    } else {
        sides.add(std::make_shared<quad>(basis1, u, v, mat));
        max.e[0] += w.e[0];
        max.e[1] += w.e[1];
    }
    bbox = Boxes(basis1, max);
}

Boxes pyramide::bounding_box() const { return bbox; }
