/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** obj_loader
*/

#include "obj_loader.hpp"
#include "primitives/triangle.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct FaceVertex {
    int v  = -1; // position index (1-based in OBJ, stored 0-based)
    int vt = -1; // UV index
};

static FaceVertex parse_face_token(const std::string& token)
{
    FaceVertex fv;
    std::istringstream ss(token);
    std::string part;
    int idx = 0;
    while (std::getline(ss, part, '/')) {
        if (!part.empty()) {
            int val = std::stoi(part);
            if (idx == 0) fv.v  = val > 0 ? val - 1 : val; // negative = relative
            if (idx == 1) fv.vt = val > 0 ? val - 1 : val;
        }
        idx++;
    }
    return fv;
}

hittable_list loadOBJ(const std::string& filename, std::shared_ptr<material> mat, double scale)
{
    hittable_list mesh;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "loadOBJ: cannot open " << filename << "\n";
        return mesh;
    }

    std::vector<point3> positions;
    std::vector<vec3>   uvs;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "v") {
            double x, y, z;
            iss >> x >> y >> z;
            positions.emplace_back(x * scale, y * scale, z * scale);

        } else if (keyword == "vt") {
            double u, v;
            iss >> u >> v;
            uvs.emplace_back(u, v, 0.0);

        } else if (keyword == "f") {
            std::vector<FaceVertex> face;
            std::string token;
            while (iss >> token)
                face.push_back(parse_face_token(token));

            // Fan triangulation for polygons (n >= 3)
            for (size_t i = 1; i + 1 < face.size(); i++) {
                const FaceVertex& a = face[0];
                const FaceVertex& b = face[i];
                const FaceVertex& c = face[i + 1];

                if (a.v < 0 || b.v < 0 || c.v < 0) continue;
                if (a.v >= (int)positions.size() ||
                    b.v >= (int)positions.size() ||
                    c.v >= (int)positions.size()) continue;

                const point3& v0 = positions[a.v];
                const point3& v1 = positions[b.v];
                const point3& v2 = positions[c.v];

                bool has_uv = (a.vt >= 0 && b.vt >= 0 && c.vt >= 0 &&
                               a.vt < (int)uvs.size() &&
                               b.vt < (int)uvs.size() &&
                               c.vt < (int)uvs.size());

                if (has_uv) {
                    mesh.add(std::make_shared<triangle>(
                        v0, v1, v2,
                        uvs[a.vt], uvs[b.vt], uvs[c.vt],
                        mat));
                } else {
                    mesh.add(std::make_shared<triangle>(v0, v1, v2, mat));
                }
            }
        }
    }

    std::clog << "loadOBJ: " << filename << " → " << mesh.objects.size() << " triangles\n";
    return mesh;
}
