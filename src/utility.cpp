/*
** EPITECH PROJECT, 2024
** rebelotte
** File description:
** utility
*/
#include "utility.hpp"

double Random::degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

double Random::random_double() {
    return rand() / (RAND_MAX + 1.0);
}

double Random::random_double(double min, double max) {
    return min + (max - min) * random_double();
}

int Random::random_int(int min, int max) {
    return int(random_double(min, max + 1));
}
