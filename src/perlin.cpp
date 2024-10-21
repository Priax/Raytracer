/*
** EPITECH PROJECT, 2024
** rebelotte
** File description:
** perlin
*/
#include "perlin.hpp"

perlin::perlin() {
    randvec = new vec3[point_count];
    for (int i = 0; i < point_count; i++) {
        randvec[i] = Vec3Utils::unit_vector(vec3::random(-1,1));
    }

    perm_x = perlin_generate_perm();
    perm_y = perlin_generate_perm();
    perm_z = perlin_generate_perm();
}

perlin::~perlin() {
    delete[] randvec;
    delete[] perm_x;
    delete[] perm_y;
    delete[] perm_z;
}

double perlin::noise(const vec3& p) const {
    double u = p.x() - floor(p.x());
    double v = p.y() - floor(p.y());
    double w = p.z() - floor(p.z());

    int i = int(floor(p.x()));
    int j = int(floor(p.y()));
    int k = int(floor(p.z()));
    vec3 c[2][2][2];

    for (int di=0; di < 2; di++)
        for (int dj=0; dj < 2; dj++)
            for (int dk=0; dk < 2; dk++)
                c[di][dj][dk] = randvec[
                    perm_x[(i+di) & 255] ^
                    perm_y[(j+dj) & 255] ^
                    perm_z[(k+dk) & 255]
                ];

    return perlin_interp(c, u, v, w);
}

double perlin::perlin_interp(const vec3 c[2][2][2], double u, double v, double w) {
    double uu = u * u * (3 - 2 * u);
    double vv = v * v * (3 - 2 * v);
    double ww = w * w * (3 - 2 * w);
    double accum = 0.0;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) {
                vec3 weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j)
                    * (1 - vv)) * (k * ww + (1 - k) * (1 - ww))
                    * c[i][j][k].dot(weight_v);
            }

    return accum;
}

double perlin::turb(const point3& p, int depth) const {
    double accum = 0.0;
    point3 temp_p = p;
    double weight = 1.0;

    for (int i = 0; i < depth; i++) {
        accum += weight * noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return fabs(accum);
}

int *perlin::perlin_generate_perm() {
    int *p = new int[point_count];

    for (int i = 0; i < point_count; i++)
        p[i] = i;

    permute(p, point_count);

    return p;
}

void perlin::permute(int* p, int n) {
    for (int i = n-1; i > 0; i--) {
        int target = Random::random_int(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}
