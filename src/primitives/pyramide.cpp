/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** pyramide
*/
#include "pyramide.hpp"
#include "triangle.hpp"

pyramide::pyramide(const point3 summit, const point3 basis1, const point3 basis2, const point3 basis3, const point3 basis4, const std::shared_ptr<material> mat) : mat(mat)
{
    sides.add(std::make_shared<triangle>(summit, basis1, basis2, mat));
    sides.add(std::make_shared<triangle>(summit, basis2, basis3, mat));
    sides.add(std::make_shared<triangle>(summit, basis3, basis4, mat));
    sides.add(std::make_shared<triangle>(summit, basis4, basis1, mat));

    sides.add(std::make_shared<triangle>(basis1, basis3, basis2, mat));
    sides.add(std::make_shared<triangle>(basis1, basis4, basis3, mat));

    point3 min_p = point3(infinity, infinity, infinity);
    point3 max_p = point3(-infinity, -infinity, -infinity);

    point3 points[5] = {summit, basis1, basis2, basis3, basis4};

    for (int i = 0; i < 5; i++) {
        for (int c = 0; c < 3; c++) {
            min_p.e[c] = std::fmin(min_p.e[c], points[i].e[c]);
            max_p.e[c] = std::fmax(max_p.e[c], points[i].e[c]);
        }
    }

    bbox = Boxes(min_p, max_p);
}

Boxes pyramide::bounding_box() const { return bbox; }
