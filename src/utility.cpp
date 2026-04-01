/*
** EPITECH PROJECT, 2024
** rebelotte
** File description:
** utility
*/
#include "utility.hpp"
#include <random>

double Random::degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

double Random::random_double() {
    thread_local std::mt19937 gen(std::random_device{}());
    thread_local std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}

double Random::random_double(double min, double max) {
    return min + (max - min) * random_double();
}

int Random::random_int(int min, int max) {
    return int(random_double(min, max + 1));
}
