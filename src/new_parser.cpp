/*
** EPITECH PROJECT, 2024
** test_libconfig
** File description:
** new_parser
*/

#include "new_parser.hpp"

newParser::newParser(libconfig::Config &config) : _cfg(config), _root(_cfg.getRoot())
{
}

void newParser::parseCamera(void)
{
    int value;
    float readFloat;
    const libconfig::Setting &camera = _root["camera"];

    if (camera.exists("resolution")) {
        camera["resolution"].lookupValue("width", value);
        _cameraRes.insert(_cameraRes.begin(), value);
        camera["resolution"].lookupValue("height", value);
        _cameraRes.push_back(value);
    } else {
        _cameraRes.push_back(400);
        _cameraRes.push_back(225);
    }
    if (camera.exists("position")) {
        camera["position"].lookupValue("x", readFloat);
        _cameraPos.insert(_cameraPos.begin(), readFloat);
        camera["position"].lookupValue("y", readFloat);
        _cameraPos.push_back(readFloat);
        camera["position"].lookupValue("z", readFloat);
        _cameraPos.push_back(readFloat);
    } else {
        for (int i = 0; i < 3; i++)
            _cameraPos.push_back(0.0);
    }
    if (camera.exists("position")) {
        camera["rotation"].lookupValue("x", readFloat);
        _cameraRot.insert(_cameraRot.begin(), readFloat);
        camera["rotation"].lookupValue("y", readFloat);
        _cameraRot.push_back(readFloat);
        camera["rotation"].lookupValue("z", readFloat);
        _cameraRot.push_back(readFloat);
    } else {
        for (int i = 0; i < 3; i++)
            _cameraPos.push_back(0.0);
    }
    if (camera.exists("fieldOfView")) {
        camera["fieldOfView"].lookupValue("angle", readFloat);
        camera_fov = readFloat;
    } else {
        camera_fov = 0.0;
    }
    if (camera.exists("background")) {
        camera["background"].lookupValue("r", readFloat);
        _BGColor.push_back(readFloat);
        camera["background"].lookupValue("g", readFloat);
        _BGColor.push_back(readFloat);
        camera["background"].lookupValue("b", readFloat);
        _BGColor.push_back(readFloat);
    } else {
        for (int i = 0; i < 3; i++)
            _cameraPos.push_back(0.0);
    }
    if (camera.exists("origin")) {
        camera["origin"].lookupValue("x", readFloat);
        _cameraOrigin.push_back(readFloat);
        camera["origin"].lookupValue("y", readFloat);
        _cameraOrigin.push_back(readFloat);
        camera["origin"].lookupValue("z", readFloat);
        _cameraOrigin.push_back(readFloat);
    } else {
        for (int i = 0; i < 3; i++)
            _cameraOrigin.push_back(0.0);
    }
    if (camera.exists("focus")) {
        camera["focus"].lookupValue("distance", readFloat);
        _cameraFocus = readFloat;
    } else {
        _cameraFocus = 0.1;
    }
    if (camera.exists("spp")) {
        camera["spp"].lookupValue("rate", _spp);
    }
    if (camera.exists("focus")) {
        camera["focus"].lookupValue("other", _cameraDistance);
    }
    if (camera.exists("depth")) {
        camera["depth"].lookupValue("max", _maxDepth);
    }
    if (camera.exists("ambient")) {
        camera["ambient"].lookupValue("scale", _ambientScale);
    }
}


void newParser::parseSpheres(void)
{
    pSphere _sphere;
    const libconfig::Setting &sph = _root["primitives"]["spheres"];
    for (int i = 0; i != sph.getLength(); i++) {
        if (sph[i].exists("rotation")) {
            sph[i]["rotation"].lookupValue("type", _sphere.rotation_type);
            sph[i]["rotation"].lookupValue("angle", _sphere.rotation_angle);
        }
        if (sph[i].exists("translation")) {
            sph[i]["translation"].lookupValue("x", _sphere.translate_x);
            sph[i]["translation"].lookupValue("y", _sphere.translate_y);
            sph[i]["translation"].lookupValue("z", _sphere.translate_z);
        }
        sph[i].lookupValue("x", _sphere.position_x);
        sph[i].lookupValue("y", _sphere.position_y);
        sph[i].lookupValue("z", _sphere.position_z);
        sph[i].lookupValue("r", _sphere.radius);
        sph[i].lookupValue("material", _sphere.material);
        if (_sphere.material != "noise") {
            if (_sphere.material == "checker") {
                sph[i]["color2"].lookupValue("r", _sphere.color_r2);
                sph[i]["color2"].lookupValue("g", _sphere.color_g2);
                sph[i]["color2"].lookupValue("b", _sphere.color_b2);
            }
            sph[i]["color"].lookupValue("r", _sphere.color_r);
            sph[i]["color"].lookupValue("g", _sphere.color_g);
            sph[i]["color"].lookupValue("b", _sphere.color_b);
        }
        sph[i].lookupValue("fuzz", _sphere.fuzz);
        _primitives._spheres.push_back(_sphere);
    }
}
void newParser::parseCone(std::string name)
{
    pCone _cone;
    const libconfig::Setting &cone = _root["primitives"][name];
    for (int i = 0; i != cone.getLength(); i++) {
        _cone.type = name;
        if (cone[i].exists("rotation")) {
            cone[i]["rotation"].lookupValue("angle", _cone.rotation_angle);
            cone[i]["rotation"].lookupValue("type", _cone.rotation_type);
        }
        if (cone[i].exists("translation")) {
            cone[i]["translation"].lookupValue("x", _cone.translate_x);
            cone[i]["translation"].lookupValue("y", _cone.translate_y);
            cone[i]["translation"].lookupValue("z", _cone.translate_z);
        }
        cone[i].lookupValue("x", _cone.position_x);
        cone[i].lookupValue("y", _cone.position_y);
        cone[i].lookupValue("z", _cone.position_z);
        cone[i].lookupValue("r", _cone.radius);
        cone[i].lookupValue("h", _cone._height);
        cone[i].lookupValue("fuzz", _cone.fuzz);
        cone[i].lookupValue("shape", _cone.type);
        cone[i].lookupValue("material", _cone.material);
        if (_cone.material != "noise") {
            if (_cone.material == "checker") {
                cone[i]["color2"].lookupValue("r", _cone.color_r2);
                cone[i]["color2"].lookupValue("g", _cone.color_g2);
                cone[i]["color2"].lookupValue("b", _cone.color_b2);
            }
            cone[i]["color"].lookupValue("r", _cone.color_r);
            cone[i]["color"].lookupValue("g", _cone.color_g);
            cone[i]["color"].lookupValue("b", _cone.color_b);
        }
        _primitives._cone.push_back(_cone);
    }
}

void newParser::parseCubes(void)
{
    pCube cube;
    const libconfig::Setting &cub = _root["primitives"]["cubes"];

    for (int i = 0; i != cub.getLength(); i++) {
        if (cub[i].exists("rotation")) {
            cub[i]["rotation"].lookupValue("angle", cube.rotation_angle);
            cub[i]["rotation"].lookupValue("type", cube.rotation_type);
        }
        if (cub[i].exists("translation")) {
            cub[i]["translation"].lookupValue("x", cube.translate_x);
            cub[i]["translation"].lookupValue("y", cube.translate_y);
            cub[i]["translation"].lookupValue("z", cube.translate_z);
        }
        cub[i]["base"].lookupValue("x", cube.position_x);
        cub[i]["base"].lookupValue("y", cube.position_y);
        cub[i]["base"].lookupValue("z", cube.position_z);
        cub[i]["top"].lookupValue("x", cube.top_x);
        cub[i]["top"].lookupValue("y", cube.top_y);
        cub[i]["top"].lookupValue("z", cube.top_z);
        cub[i].lookupValue("material", cube.material);
        cub[i].lookupValue("fuzz", cube.fuzz);
        if (cube.material != "noise") {
            if (cube.material == "checker") {
                cub[i]["color2"].lookupValue("r", cube.color_r2);
                cub[i]["color2"].lookupValue("g", cube.color_g2);
                cub[i]["color2"].lookupValue("b", cube.color_b2);
            }
            cub[i]["color"].lookupValue("r", cube.color_r);
            cub[i]["color"].lookupValue("g", cube.color_g);
            cub[i]["color"].lookupValue("b", cube.color_b);
        }
        _primitives._cubes.push_back(cube);
    }
}

void newParser::parseTriangles(void)
{
    pTri triangle;
    const libconfig::Setting &tri = _root["primitives"]["triangles"];

    for (int i = 0; i != tri.getLength(); i++) {
        if (tri[i].exists("rotation")) {
            tri[i]["rotation"].lookupValue("angle", triangle.rotation_angle);
            tri[i]["rotation"].lookupValue("type", triangle.rotation_type);
        }
        if (tri[i].exists("translation")) {
            tri[i]["translation"].lookupValue("x", triangle.translate_x);
            tri[i]["translation"].lookupValue("y", triangle.translate_y);
            tri[i]["translation"].lookupValue("z", triangle.translate_z);
        }
        tri[i]["top"].lookupValue("x", triangle.position_x);
        tri[i]["top"].lookupValue("y", triangle.position_y);
        tri[i]["top"].lookupValue("z", triangle.position_z);
        tri[i]["left"].lookupValue("x", triangle.left_x);
        tri[i]["left"].lookupValue("y", triangle.left_y);
        tri[i]["left"].lookupValue("z", triangle.left_z);
        tri[i]["right"].lookupValue("x", triangle.right_x);
        tri[i]["right"].lookupValue("y", triangle.right_y);
        tri[i]["right"].lookupValue("z", triangle.right_z);
        tri[i].lookupValue("material", triangle.material);
        tri[i].lookupValue("fuzz", triangle.fuzz);
        if (triangle.material != "noise") {
            if (triangle.material == "checker") {
                tri[i]["color2"].lookupValue("r", triangle.color_r2);
                tri[i]["color2"].lookupValue("g", triangle.color_g2);
                tri[i]["color2"].lookupValue("b", triangle.color_b2);
            }
            tri[i]["color"].lookupValue("r", triangle.color_r);
            tri[i]["color"].lookupValue("g", triangle.color_g);
            tri[i]["color"].lookupValue("b", triangle.color_b);
        }
        _primitives._triangles.push_back(triangle);
    }
}

void newParser::parsePyramids(void)
{
    pPyra new_pyramid;
    const libconfig::Setting &pyramid = _root["primitives"]["pyramids"];

    for (int i = 0; i != pyramid.getLength(); i++) {
        if (pyramid[i].exists("rotation")) {
            pyramid[i]["rotation"].lookupValue("angle", new_pyramid.rotation_angle);
            pyramid[i]["rotation"].lookupValue("type", new_pyramid.rotation_type);
        }
        if (pyramid[i].exists("translation")) {
            pyramid[i]["translation"].lookupValue("x", new_pyramid.translate_x);
            pyramid[i]["translation"].lookupValue("y", new_pyramid.translate_y);
            pyramid[i]["translation"].lookupValue("z", new_pyramid.translate_z);
        }
        pyramid[i]["top"].lookupValue("x", new_pyramid.position_x);
        pyramid[i]["top"].lookupValue("y", new_pyramid.position_y);
        pyramid[i]["top"].lookupValue("z", new_pyramid.position_z);
        pyramid[i]["basis1"].lookupValue("x", new_pyramid.basis_1_x);
        pyramid[i]["basis1"].lookupValue("y", new_pyramid.basis_1_y);
        pyramid[i]["basis1"].lookupValue("z", new_pyramid.basis_1_z);
        pyramid[i]["basis2"].lookupValue("x", new_pyramid.basis_2_x);
        pyramid[i]["basis2"].lookupValue("y", new_pyramid.basis_2_y);
        pyramid[i]["basis2"].lookupValue("z", new_pyramid.basis_2_z);
        pyramid[i]["basis3"].lookupValue("x", new_pyramid.basis_3_x);
        pyramid[i]["basis3"].lookupValue("y", new_pyramid.basis_3_y);
        pyramid[i]["basis3"].lookupValue("z", new_pyramid.basis_3_z);
        pyramid[i]["basis4"].lookupValue("x", new_pyramid.basis_4_x);
        pyramid[i]["basis4"].lookupValue("y", new_pyramid.basis_4_y);
        pyramid[i]["basis4"].lookupValue("z", new_pyramid.basis_4_z);
        pyramid[i].lookupValue("material", new_pyramid.material);
        pyramid[i].lookupValue("fuzz", new_pyramid.fuzz);
        if (new_pyramid.material != "noise") {
            if (new_pyramid.material == "checker") {
                pyramid[i]["color2"].lookupValue("r", new_pyramid.color_r2);
                pyramid[i]["color2"].lookupValue("g", new_pyramid.color_g2);
                pyramid[i]["color2"].lookupValue("b", new_pyramid.color_b2);
            }
            pyramid[i]["color"].lookupValue("r", new_pyramid.color_r);
            pyramid[i]["color"].lookupValue("g", new_pyramid.color_g);
            pyramid[i]["color"].lookupValue("b", new_pyramid.color_b);
        }
        _primitives._pyramids.push_back(new_pyramid);
    }
}

void newParser::parseCylinder(std::string name)
{
    pCyli _cylinder;
    const libconfig::Setting &cylinder = _root["primitives"][name];
    for (int i = 0; i != cylinder.getLength(); i++) {
        _cylinder.type = name;
        if (cylinder[i].exists("rotation")) {
            cylinder[i]["rotation"].lookupValue("angle", _cylinder.rotation_angle);
            cylinder[i]["rotation"].lookupValue("type", _cylinder.rotation_type);
        }
        if (cylinder[i].exists("translation")) {
            cylinder[i]["translation"].lookupValue("x", _cylinder.translate_x);
            cylinder[i]["translation"].lookupValue("y", _cylinder.translate_y);
            cylinder[i]["translation"].lookupValue("z", _cylinder.translate_z);
        }
        cylinder[i]["base"].lookupValue("x", _cylinder.base_x);
        cylinder[i]["base"].lookupValue("y", _cylinder.base_y);
        cylinder[i]["base"].lookupValue("z", _cylinder.base_z);
        cylinder[i]["top"].lookupValue("x", _cylinder.position_x);
        cylinder[i]["top"].lookupValue("y", _cylinder.position_y);
        cylinder[i]["top"].lookupValue("z", _cylinder.position_z);
        cylinder[i].lookupValue("r", _cylinder.radius);
        cylinder[i].lookupValue("material", _cylinder.material);
        cylinder[i].lookupValue("fuzz", _cylinder.fuzz);
        if (_cylinder.material != "noise") {
            if (_cylinder.material == "checker") {
                cylinder[i]["color2"].lookupValue("r", _cylinder.color_r2);
                cylinder[i]["color2"].lookupValue("g", _cylinder.color_g2);
                cylinder[i]["color2"].lookupValue("b", _cylinder.color_b2);
            }
            cylinder[i]["color"].lookupValue("r", _cylinder.color_r);
            cylinder[i]["color"].lookupValue("g", _cylinder.color_g);
            cylinder[i]["color"].lookupValue("b", _cylinder.color_b);
            _primitives._cylinders.push_back(_cylinder);
        }
    }
}

void newParser::parsePlanes(void)
{
    pPlanes plane;
    const libconfig::Setting &plan = _root["primitives"]["planes"];

    for (int i = 0; i != plan.getLength(); i++) {
        if (plan[i].exists("rotation")) {
            plan[i]["rotation"].lookupValue("angle", plane.rotation_angle);
            plan[i]["rotation"].lookupValue("type", plane.rotation_type);
        }
        if (plan[i].exists("translation")) {
            plan[i]["translation"].lookupValue("x", plane.translate_x);
            plan[i]["translation"].lookupValue("y", plane.translate_y);
            plan[i]["translation"].lookupValue("z", plane.translate_z);
        }
        plan[i]["pos"].lookupValue("x", plane.position_x);
        plan[i]["pos"].lookupValue("y", plane.position_y);
        plan[i]["pos"].lookupValue("z", plane.position_z);
        plan[i]["dir"].lookupValue("x", plane.dir_x);
        plan[i]["dir"].lookupValue("y", plane.dir_y);
        plan[i]["dir"].lookupValue("z", plane.dir_z);
        plan[i]["axis"].lookupValue("x", plane.axis_x);
        plan[i]["axis"].lookupValue("y", plane.axis_y);
        plan[i]["axis"].lookupValue("z", plane.axis_z);
        plan[i].lookupValue("material", plane.material);
        if (plane.material != "noise") {
            if (plane.material == "checker") {
                plan[i]["color2"].lookupValue("r", plane.color_r2);
                plan[i]["color2"].lookupValue("g", plane.color_g2);
                plan[i]["color2"].lookupValue("b", plane.color_b2);
            }
            plan[i]["color"].lookupValue("r", plane.color_r);
            plan[i]["color"].lookupValue("g", plane.color_g);
            plan[i]["color"].lookupValue("b", plane.color_b);
        }
        _primitives._planes.push_back(plane);
    }
}

pPointLight newParser::parseLitSphere(const libconfig::Setting &light)
{
    pPointLight out;

    light.lookupValue("x", out._position_sphere.position_x);
    light.lookupValue("y", out._position_sphere.position_y);
    light.lookupValue("z", out._position_sphere.position_z);
    light.lookupValue("r", out._position_sphere.radius);
    light.lookupValue("shape", out._position_sphere.type);
    light.lookupValue("fuzz", out._position_sphere.fuzz);
    light["color"].lookupValue("r", out._position_sphere.color_r);
    light["color"].lookupValue("g", out._position_sphere.color_g);
    light["color"].lookupValue("b", out._position_sphere.color_b);

    return out;
}

pPointLight newParser::parseLitCylinder(const libconfig::Setting &light)
{
    pPointLight out;

    light["base"].lookupValue("x", out._position_cylinder.base_x);
    light["base"].lookupValue("y", out._position_cylinder.base_y);
    light["base"].lookupValue("z", out._position_cylinder.base_z);
    light["top"].lookupValue("x", out._position_cylinder.position_x);
    light["top"].lookupValue("y", out._position_cylinder.position_y);
    light["top"].lookupValue("z", out._position_cylinder.position_z);
    light.lookupValue("shape", out._position_cylinder.type);
    light.lookupValue("r", out._position_cylinder.radius);
    light.lookupValue("fuzz", out._position_cylinder.fuzz);
    light["color"].lookupValue("r", out._position_cylinder.color_r);
    light["color"].lookupValue("g", out._position_cylinder.color_g);
    light["color"].lookupValue("b", out._position_cylinder.color_b);

    return out;
}
pPointLight newParser::parseLitCone(const libconfig::Setting &light)
{
    pPointLight out;

    light.lookupValue("x", out._position_cone.position_x);
    light.lookupValue("y", out._position_cone.position_y);
    light.lookupValue("z", out._position_cone.position_z);
    light.lookupValue("r", out._position_cone.radius);
    light.lookupValue("h", out._position_cone._height);
    light.lookupValue("shape", out._position_cone.type);
    light.lookupValue("fuzz", out._position_cone.fuzz);
    light["color"].lookupValue("r", out._position_cone.color_r);
    light["color"].lookupValue("g", out._position_cone.color_g);
    light["color"].lookupValue("b", out._position_cone.color_b);

    return out;
}
void newParser::parseLights(void)
{
    const libconfig::Setting &light = _root["lights"]["point"];
    pPointLight newL;
    std::string name;
    for (int i = 0; i != light.getLength(); i++) {
        light[i].lookupValue("shape", name);
        if (name == "sphere") {
            newL = parseLitSphere(light[i]);
            _lights.push_back(newL);
            continue;
        }
        if (name == "cylinder") {
            newL = parseLitCylinder(light[i]);
            _lights.push_back(newL);
            continue;
        }
        if (name == "cone") {
            newL = parseLitCone(light[i]);
            _lights.push_back(newL);
            continue;
        }
    }
}

void newParser::parsePrimitives(void)
{
    const libconfig::Setting &prim = _root["primitives"];
    std::string name;

    for (int i = 0; i != prim.getLength(); i++) {
        name = prim[i].getName();
        if (name == "spheres") {
            parseSpheres();
        }
        if (name == "cylinders" || name == "limcylinders") {
            parseCylinder(name);
        }
        if (name == "cones" || name == "limcones") {
            parseCone(name);
        }
        if (name == "planes") {
            parsePlanes();
        }
        if (name == "cubes") {
            parseCubes();
        }
        if (name == "triangles") {
            parseTriangles();
        }
        if (name == "pyramids") {
            parsePyramids();
        }
    }
}

//? gestion d'erreur
//? formes nouvelles : triangles, cubes, ???
//? rotations, transformations

hittable_list newParser::setDataPrim(hittable_list world)
{
    std::shared_ptr<material> my_mat;
    std::shared_ptr<hittable> shape;
    for (size_t i = 0; i != _primitives._spheres.size(); i++) {
        my_mat = createShapeMat(_primitives._spheres[i].material, _primitives._spheres[i]);
        shape = createShape(point3(_primitives._spheres[i].position_x,
        _primitives._spheres[i].position_y, _primitives._spheres[i].position_z),
        _primitives._spheres[i].radius, my_mat, _primitives._spheres[i].rotation_angle, _primitives._spheres[i].rotation_type,
        vec3(_primitives._spheres[i].translate_x, _primitives._spheres[i].translate_y, _primitives._spheres[i].translate_z));
        world.add(shape);
    }
    for (size_t i = 0; i != _primitives._cone.size(); i++) {
        my_mat = createShapeMat(_primitives._cone[i].material, _primitives._cone[i]);
        shape = createShape(_primitives._cone[i].type, point3(_primitives._cone[i].position_x,
        _primitives._cone[i].position_y, _primitives._cone[i].position_z),
        _primitives._cone[i].radius, _primitives._cone[i]._height, my_mat, _primitives._cone[i].rotation_angle,
        _primitives._cone[i].rotation_type,
        vec3(_primitives._cone[i].translate_x, _primitives._cone[i].translate_y, _primitives._cone[i].translate_z));
        world.add(shape);
    }
    for (size_t i = 0; i != _primitives._cylinders.size(); i++) {
        my_mat = createShapeMat(_primitives._cylinders[i].material, _primitives._cylinders[i]);
        shape = createShape(_primitives._cylinders[i].type, point3(_primitives._cylinders[i].base_x,
        _primitives._cylinders[i].base_y, _primitives._cylinders[i].base_z), point3(_primitives._cylinders[i].position_x,
        _primitives._cylinders[i].position_y, _primitives._cylinders[i].position_z), _primitives._cylinders[i].radius, my_mat,
        _primitives._cylinders[i].rotation_angle, _primitives._cylinders[i].rotation_type, vec3(_primitives._cylinders[i].translate_x,
        _primitives._cylinders[i].translate_y, _primitives._cylinders[i].translate_z));
        world.add(shape);
    }
    for (size_t i = 0; i != _primitives._planes.size(); i++) {
        my_mat = createShapeMat(_primitives._planes[i].material, _primitives._planes[i]);
        shape = createShape(point3(_primitives._planes[i].position_x, _primitives._planes[i].position_y, _primitives._planes[i].position_z),
        point3(_primitives._planes[i].dir_x, _primitives._planes[i].dir_y, _primitives._planes[i].dir_z),
        vec3(_primitives._planes[i].axis_x, _primitives._planes[i].axis_y, _primitives._planes[i].axis_z), my_mat,
        _primitives._planes[i].rotation_angle, _primitives._planes[i].rotation_type,
        vec3(_primitives._planes[i].translate_x, _primitives._planes[i].translate_y, _primitives._planes[i].translate_z));
        world.add(shape);
    }
    for (size_t i = 0; i != _primitives._cubes.size(); i++) {
        my_mat = createShapeMat(_primitives._cubes[i].material, _primitives._cubes[i]);
        shape = createShape(point3(_primitives._cubes[i].position_x, _primitives._cubes[i].position_y, _primitives._cubes[i].position_z),
        point3(_primitives._cubes[i].top_x, _primitives._cubes[i].top_y, _primitives._cubes[i].top_z), my_mat,
        _primitives._cubes[i].rotation_angle, _primitives._cubes[i].rotation_type, vec3(_primitives._cubes[i].translate_x,
        _primitives._cubes[i].translate_y, _primitives._cubes[i].translate_z));
        world.add(shape);
    }
    for (size_t i = 0; i != _primitives._triangles.size(); i++) {
        my_mat = createShapeMat(_primitives._triangles[i].material, _primitives._triangles[i]);
        shape = createShape(point3(_primitives._triangles[i].position_x, _primitives._triangles[i].position_y,
        _primitives._triangles[i].position_z), point3(_primitives._triangles[i].left_x, _primitives._triangles[i].left_y,
        _primitives._triangles[i].left_z), point3(_primitives._triangles[i].right_x, _primitives._triangles[i].right_y,
        _primitives._triangles[i].right_z), my_mat, _primitives._triangles[i].rotation_angle,
        _primitives._triangles[i].rotation_type,
        vec3(_primitives._triangles[i].translate_x, _primitives._triangles[i].translate_y, _primitives._triangles[i].translate_z));
        world.add(shape);
    }
    for (size_t i = 0; i != _primitives._pyramids.size(); i++) {
        my_mat = createShapeMat(_primitives._pyramids[i].material, _primitives._pyramids[i]);
        shape = createShape(point3(_primitives._pyramids[i].position_x, _primitives._pyramids[i].position_y, _primitives._pyramids[i].position_z),
        point3(_primitives._pyramids[i].basis_1_x, _primitives._pyramids[i].basis_1_y, _primitives._pyramids[i].basis_1_z),
        point3(_primitives._pyramids[i].basis_2_x, _primitives._pyramids[i].basis_2_y, _primitives._pyramids[i].basis_2_z),
        point3(_primitives._pyramids[i].basis_3_x, _primitives._pyramids[i].basis_3_y, _primitives._pyramids[i].basis_3_z),
        point3(_primitives._pyramids[i].basis_4_x, _primitives._pyramids[i].basis_4_y, _primitives._pyramids[i].basis_4_z),
        my_mat, _primitives._pyramids[i].rotation_angle, _primitives._pyramids[i].rotation_type,
        vec3(_primitives._pyramids[i].translate_x, _primitives._pyramids[i].translate_y, _primitives._pyramids[i].translate_z));
        world.add(shape);
    }
    return world;
}

camera newParser::setDataCam(camera cam)
{
    cam.image_width = _cameraRes[0];
    cam.image_height = _cameraRes[1];
    cam.vfov = camera_fov;
    cam.samples_per_pixel = _spp;
    cam.max_depth = _maxDepth;
    cam.background = color(_BGColor[0], _BGColor[1], _BGColor[2]);
    cam.lookfrom = point3(_cameraPos[0], _cameraPos[1], _cameraPos[2]);
    cam.lookat = point3(_cameraOrigin[0], _cameraOrigin[1], _cameraOrigin[2]);
    cam.vup = vec3(_cameraRot[0], _cameraRot[1], _cameraRot[2]);
    cam.defocus_angle = _cameraFocus;
    cam.focus_dist = _cameraDistance;
    return cam;
}

size_t newParser::getCameraSize(std::string element)
{
    if (element.compare("height"))
        return _cameraRes[0];
    if (element.compare("width"))
        return _cameraRes[1];
    return 0;
}

hittable_list newParser::setDataLights(hittable_list lights)
{
    for (std::vector<pPointLight>::size_type i = 0; i != _lights.size(); i++) {
        if (!_lights[i]._position_cylinder.type.empty()) {
            lights.add(std::make_shared<Cylinder>(
                point3(_lights[i]._position_cylinder.base_x, _lights[i]._position_cylinder.base_y, _lights[i]._position_cylinder.base_z),
                point3(_lights[i]._position_cylinder.position_x, _lights[i]._position_cylinder.position_y, _lights[i]._position_cylinder.position_z),
                _lights[i]._position_cylinder.radius, std::make_shared<diffuse_light>(color(_lights[i]._position_cylinder.color_r,
                _lights[i]._position_cylinder.color_g, _lights[i]._position_cylinder.color_g))));
        }
        if (!_lights[i]._position_cone.type.empty()) {
            lights.add(std::make_shared<Cone>(point3(_lights[i]._position_cone.position_x, _lights[i]._position_cone.position_y, _lights[i]._position_cone.position_z),
            _lights[i]._position_cone.radius, _lights[i]._position_cone._height,
            std::make_shared<diffuse_light>(color(_lights[i]._position_cone.color_r, _lights[i]._position_cone.color_g, _lights[i]._position_cone.color_b))));
        }
        if (!_lights[i]._position_sphere.type.empty()) {
            lights.add(std::make_shared<sphere>(point3(_lights[i]._position_sphere.position_x, _lights[i]._position_sphere.position_y, _lights[i]._position_sphere.position_z),
            _lights[i]._position_sphere.radius, std::make_shared<diffuse_light>(color(_lights[i]._position_cone.color_r, _lights[i]._position_cone.color_g, _lights[i]._position_cone.color_b))));
        }
    }
    return lights;
}

std::shared_ptr<hittable> newParser::createShape(point3 pos, double radius, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation)
{
    std::shared_ptr<hittable> my_shape = std::make_shared<sphere>(pos, radius, material_ptr);

    if (rotation_type == "x") {
        my_shape = std::make_shared<rotate_x>(my_shape, rotation);
    } else if (rotation_type == "y") {
        my_shape = std::make_shared<rotate_y>(my_shape, rotation);
    } else {
        my_shape = std::make_shared<rotate_z>(my_shape, rotation);
    }
    return std::make_shared<translate>(my_shape, translation);
}

std::shared_ptr<hittable> newParser::createShape(std::string shape, point3 pos, double radius, double height, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation)
{
    std::shared_ptr<hittable> my_shape;

    if (shape == "limcones") {
        my_shape = std::make_shared<LimCone>(pos, radius, height, material_ptr);
    } else {
        my_shape = std::make_shared<Cone>(pos, radius, height, material_ptr);
    }
    if (rotation_type == "x") {
        my_shape = std::make_shared<rotate_x>(my_shape, rotation);
    } else if (rotation_type == "y") {
        my_shape = std::make_shared<rotate_y>(my_shape, rotation);
    } else {
        my_shape = std::make_shared<rotate_z>(my_shape, rotation);
    }
    return std::make_shared<translate>(my_shape, translation);
}

std::shared_ptr<hittable> newParser::createShape(std::string shape, point3 base, point3 top, double radius, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation)
{
    std::shared_ptr<hittable> my_shape;

    if (shape == "limcylinders") {
        my_shape = std::make_shared<LimCylinder>(base, top, radius, material_ptr);

    } else {
        my_shape = std::make_shared<Cylinder>(base, top, radius, material_ptr);
    }
    if (rotation_type == "x") {
        my_shape = std::make_shared<rotate_x>(my_shape, rotation);
    } else if (rotation_type == "y") {
        my_shape = std::make_shared<rotate_y>(my_shape, rotation);
    } else {
        my_shape = std::make_shared<rotate_z>(my_shape, rotation);
    }
    return std::make_shared<translate>(my_shape, translation);
}

std::shared_ptr<hittable> newParser::createShape(point3 pos, point3 dir, vec3 rot, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation)
{
    std::shared_ptr<hittable> my_shape;

    my_shape = std::make_shared<quad>(pos, dir, rot, material_ptr);
    if (rotation_type == "x") {
        my_shape = std::make_shared<rotate_x>(my_shape, rotation);
    } else if (rotation_type == "y") {
        my_shape = std::make_shared<rotate_y>(my_shape, rotation);
    } else {
        my_shape = std::make_shared<rotate_z>(my_shape, rotation);
    }
    return std::make_shared<translate>(my_shape, translation);
}

std::shared_ptr<hittable> newParser::createShape(point3 bot, point3 top, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation)
{
    std::shared_ptr<hittable> my_shape = std::make_shared<Cube>(bot, top, material_ptr);

    if (rotation_type == "x") {
        my_shape = std::make_shared<rotate_x>(my_shape, rotation);
    } else if (rotation_type == "y") {
        my_shape = std::make_shared<rotate_y>(my_shape, rotation);
    } else {
        my_shape = std::make_shared<rotate_z>(my_shape, rotation);
    }
    return std::make_shared<translate>(my_shape, translation);
}

std::shared_ptr<hittable> newParser::createShape(point3 down, point3 left, point3 right, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation)
{
    std::shared_ptr<hittable> my_shape = std::make_shared<triangle>(down, left, right, material_ptr);

    if (rotation_type == "x") {
        my_shape = std::make_shared<rotate_x>(my_shape, rotation);
    } else if (rotation_type == "y") {
        my_shape = std::make_shared<rotate_y>(my_shape, rotation);
    } else {
        my_shape = std::make_shared<rotate_z>(my_shape, rotation);
    }
    return std::make_shared<translate>(my_shape, translation);
}

std::shared_ptr<hittable> newParser::createShape(point3 top, point3 basis1, point3 basis2, point3 basis3, point3 basis4, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation)
{
    std::shared_ptr<hittable> my_shape = std::make_shared<pyramide>(top, basis1, basis2, basis3, basis4, material_ptr);

    if (rotation_type == "x") {
        my_shape = std::make_shared<rotate_x>(my_shape, rotation);
    } else if (rotation_type == "y") {
        my_shape = std::make_shared<rotate_y>(my_shape, rotation);
    } else {
        my_shape = std::make_shared<rotate_z>(my_shape, rotation);
    }
    return std::make_shared<translate>(my_shape, translation);
}

std::shared_ptr<metal> newParser::createMaterial(color colors, double fuzz)
{
    return std::make_shared<metal>(colors, fuzz);
}

std::shared_ptr<lambertian> newParser::createMaterial(color colors)
{
    return std::make_shared<lambertian>(colors);
}

std::shared_ptr<dielectric> newParser::createMaterial(double refraction_index)
{
    return std::make_shared<dielectric>(refraction_index);
}

std::shared_ptr<diffuse_light> newParser::createMaterial(color colors, char c)
{
    (void)c;
    return std::make_shared<diffuse_light>(colors);
}

std::shared_ptr<lambertian> newParser::createTexture(double scale)
{
    return std::make_shared<lambertian>(std::make_shared<noise_texture>(scale));
}

std::shared_ptr<lambertian> newParser::createTexture(color color1, color color2, double scale)
{
    return std::make_shared<lambertian>(std::make_shared<checker_texture>(scale, color1, color2));
}

std::shared_ptr<material> newParser::createShapeMat(std::string type, pSphere sphere)
{
    if (type == "metal") {
        return createMaterial(color(sphere.color_r, sphere.color_g, sphere.color_b), sphere.fuzz);
    }
    if (type == "glass") {
        return createMaterial(sphere.fuzz);
    }
    if (type == "solid") {
        return createMaterial(color(sphere.color_r, sphere.color_g, sphere.color_b));
    }
    if (type == "light") {
        return createMaterial(color(sphere.color_r, sphere.color_g, sphere.color_b), 'c');
    }
    if (type == "noise") {
        return createTexture(sphere.fuzz);
    }
    if (type == "checker") {
        return createTexture(color(sphere.color_r, sphere.color_g, sphere.color_b),
        color(sphere.color_r2, sphere.color_g2, sphere.color_b2), sphere.fuzz);
    }
    return nullptr;
}

std::shared_ptr<material> newParser::createShapeMat(std::string type, pCone cone)
{
    if (type == "metal") {
        return createMaterial(color(cone.color_r, cone.color_g, cone.color_b), cone.fuzz);
    }
    if (type == "glass") {
        return createMaterial(cone.fuzz);
    }
    if (type == "solid") {
        return createMaterial(color(cone.color_r, cone.color_g, cone.color_b));
    }
    if (type == "light") {
        return createMaterial(color(cone.color_r, cone.color_g, cone.color_b), 'c');
    }
    if (type == "noise") {
        return createTexture(cone.fuzz);
    }
    if (type == "checker") {
        return createTexture(color(cone.color_r, cone.color_g, cone.color_b),
        color(cone.color_r2, cone.color_g2, cone.color_b2), cone.fuzz);
    }
    return nullptr;
}

std::shared_ptr<material> newParser::createShapeMat(std::string type, pCyli cylinder)
{
    if (type == "metal") {
        return createMaterial(color(cylinder.color_r, cylinder.color_g, cylinder.color_b), cylinder.fuzz);
    }
    if (type == "glass") {
        return createMaterial(cylinder.fuzz);
    }
    if (type == "solid") {
        return createMaterial(color(cylinder.color_r, cylinder.color_g, cylinder.color_b));
    }
    if (type == "light") {
        return createMaterial(color(cylinder.color_r, cylinder.color_g, cylinder.color_b), 'c');
    }
    if (type == "noise") {
        return createTexture(cylinder.fuzz);
    }
    if (type == "checker") {
        return createTexture(color(cylinder.color_r, cylinder.color_g, cylinder.color_b),
        color(cylinder.color_r2, cylinder.color_g2, cylinder.color_b2), cylinder.fuzz);
    }
    return nullptr;
}

std::shared_ptr<material> newParser::createShapeMat(std::string type, pPlanes planes)
{
    if (type == "metal") {
        return createMaterial(color(planes.color_r, planes.color_g, planes.color_b), planes.fuzz);
    }
    if (type == "glass") {
        return createMaterial(planes.fuzz);
    }
    if (type == "solid") {
        return createMaterial(color(planes.color_r, planes.color_g, planes.color_b));
    }
    if (type == "light") {
        return createMaterial(color(planes.color_r, planes.color_g, planes.color_b), 'c');
    }
    if (type == "noise") {
        return createTexture(planes.fuzz);
    }
    if (type == "checker") {
        return createTexture(color(planes.color_r, planes.color_g, planes.color_b),
        color(planes.color_r2, planes.color_g2, planes.color_b2), planes.fuzz);
    }
    return nullptr;
}
std::shared_ptr<material> newParser::createShapeMat(std::string type, pCube cube)
{
    if (type == "metal") {
        return createMaterial(color(cube.color_r, cube.color_g, cube.color_b), cube.fuzz);
    }
    if (type == "glass") {
        return createMaterial(cube.fuzz);
    }
    if (type == "solid") {
        return createMaterial(color(cube.color_r, cube.color_g, cube.color_b));
    }
    if (type == "light") {
        return createMaterial(color(cube.color_r, cube.color_g, cube.color_b), 'c');
    }
    if (type == "noise") {
        return createTexture(cube.fuzz);
    }
    if (type == "checker") {
        return createTexture(color(cube.color_r, cube.color_g, cube.color_b),
        color(cube.color_r2, cube.color_g2, cube.color_b2), cube.fuzz);
    }
    return nullptr;
}

std::shared_ptr<material> newParser::createShapeMat(std::string type, pTri triangle)
{
    if (type == "metal") {
        return createMaterial(color(triangle.color_r, triangle.color_g, triangle.color_b), triangle.fuzz);
    }
    if (type == "glass") {
        return createMaterial(triangle.fuzz);
    }
    if (type == "solid") {
        return createMaterial(color(triangle.color_r, triangle.color_g, triangle.color_b));
    }
    if (type == "light") {
        return createMaterial(color(triangle.color_r, triangle.color_g, triangle.color_b), 'c');
    }
    if (type == "noise") {
        return createTexture(triangle.fuzz);
    }
    if (type == "checker") {
        return createTexture(color(triangle.color_r, triangle.color_g, triangle.color_b),
        color(triangle.color_r2, triangle.color_g2, triangle.color_b2), triangle.fuzz);
    }
    return nullptr;
}

std::shared_ptr<material> newParser::createShapeMat(std::string type, pPyra pyramid)
{
    if (type == "metal") {
        return createMaterial(color(pyramid.color_r, pyramid.color_g, pyramid.color_b), pyramid.fuzz);
    }
    if (type == "glass") {
        return createMaterial(pyramid.fuzz);
    }
    if (type == "solid") {
        return createMaterial(color(pyramid.color_r, pyramid.color_g, pyramid.color_b));
    }
    if (type == "noise") {
        return createTexture(pyramid.fuzz);
    }
    if (type == "checker") {
        return createTexture(color(pyramid.color_r, pyramid.color_g, pyramid.color_b),
        color(pyramid.color_r2, pyramid.color_g2, pyramid.color_b2), pyramid.fuzz);
    }
    return nullptr;
}

void newParser::checkValidity(void)
{
    int flag = 0;

    if (!_root.exists("camera")) {
        throw errorParser(errorParser::WRONG_NAME);
    }

    const libconfig::Setting& camera = _root["camera"];
    if(!camera.exists("resolution"))
        if (camera["resolution"]["width"].getType() != libconfig::Setting::TypeInt ||
        camera["resolution"]["height"].getType() != libconfig::Setting::TypeInt) {
            throw errorParser(errorParser::WRONG_TYPE);
        }
    if (camera["position"]["x"].getType() != libconfig::Setting::TypeFloat ||
       camera["position"]["y"].getType() != libconfig::Setting::TypeFloat ||
       camera["position"]["z"].getType() != libconfig::Setting::TypeFloat) {
        throw errorParser(errorParser::WRONG_TYPE);
    }
    if (camera["rotation"]["x"].getType() != libconfig::Setting::TypeFloat ||
       camera["rotation"]["y"].getType() != libconfig::Setting::TypeFloat ||
       camera["rotation"]["z"].getType() != libconfig::Setting::TypeFloat) {
        throw errorParser(errorParser::WRONG_TYPE);
    }
    if (camera["fieldOfView"]["angle"].getType() != libconfig::Setting::TypeFloat) {
        throw errorParser(errorParser::WRONG_TYPE);
    }

    const libconfig::Setting& primitives = _root["primitives"];
    if (_root["primitives"].exists("spheres")) {
        const libconfig::Setting& spheres = primitives["spheres"];
        for (int i = 0; i < spheres.getLength(); ++i) {
            const libconfig::Setting& sphere = spheres[i];
            if (sphere["x"].getType() != libconfig::Setting::TypeFloat ||
            sphere["y"].getType() != libconfig::Setting::TypeFloat ||
            sphere["z"].getType() != libconfig::Setting::TypeFloat ||
            sphere["r"].getType() != libconfig::Setting::TypeFloat ||
            sphere["material"].getType() != libconfig::Setting::TypeString ||
            sphere["fuzz"].getType() != libconfig::Setting::TypeFloat) {
                throw errorParser(errorParser::WRONG_TYPE);
            }
        }
        flag++;
    }

    if (_root["primitives"].exists("cylinders")) {
        const libconfig::Setting& cylinders = primitives["cylinders"];
        for (int i = 0; i < cylinders.getLength(); ++i) {
            const libconfig::Setting& cylinder = cylinders[i];
            if (cylinder["base"]["x"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["base"]["y"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["base"]["z"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["top"]["x"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["top"]["y"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["top"]["z"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["r"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["material"].getType() != libconfig::Setting::TypeString ||
            cylinder["color"]["r"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["color"]["g"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["color"]["b"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["fuzz"].getType() != libconfig::Setting::TypeFloat) {
                throw errorParser(errorParser::WRONG_TYPE);
            }
        }
        flag++;
    }
    if (_root["primitives"].exists("limcylinders")) {
        const libconfig::Setting& cylinders = primitives["limcylinders"];
        for (int i = 0; i < cylinders.getLength(); ++i) {
            const libconfig::Setting& cylinder = cylinders[i];
            if (cylinder["base"]["x"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["base"]["y"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["base"]["z"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["top"]["x"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["top"]["y"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["top"]["z"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["r"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["material"].getType() != libconfig::Setting::TypeString ||
            cylinder["color"]["r"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["color"]["g"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["color"]["b"].getType() != libconfig::Setting::TypeFloat ||
            cylinder["fuzz"].getType() != libconfig::Setting::TypeFloat) {
                throw errorParser(errorParser::WRONG_TYPE);
            }
        }
        flag++;
    }
    if (_root["primitives"].exists("cones")) {
        const libconfig::Setting& cones = primitives["cones"];
        for (int i = 0; i < cones.getLength(); ++i) {
            const libconfig::Setting& cone = cones[i];
            if (cone["x"].getType() != libconfig::Setting::TypeFloat ||
            cone["y"].getType() != libconfig::Setting::TypeFloat ||
            cone["z"].getType() != libconfig::Setting::TypeFloat ||
            cone["r"].getType() != libconfig::Setting::TypeFloat ||
            cone["h"].getType() != libconfig::Setting::TypeFloat ||
            cone["material"].getType() != libconfig::Setting::TypeString ||
            cone["color"]["r"].getType() != libconfig::Setting::TypeFloat ||
            cone["color"]["g"].getType() != libconfig::Setting::TypeFloat ||
            cone["color"]["b"].getType() != libconfig::Setting::TypeFloat ||
            cone["fuzz"].getType() != libconfig::Setting::TypeFloat) {
                throw errorParser(errorParser::WRONG_TYPE);
            }
        }
        flag++;
    }
    if (_root["primitives"].exists("limcones")) {
        const libconfig::Setting& cones = primitives["limcones"];
        for (int i = 0; i < cones.getLength(); ++i) {
            const libconfig::Setting& cone = cones[i];
            if (cone["x"].getType() != libconfig::Setting::TypeFloat ||
            cone["y"].getType() != libconfig::Setting::TypeFloat ||
            cone["z"].getType() != libconfig::Setting::TypeFloat ||
            cone["r"].getType() != libconfig::Setting::TypeFloat ||
            cone["h"].getType() != libconfig::Setting::TypeFloat ||
            cone["material"].getType() != libconfig::Setting::TypeString ||
            cone["color"]["r"].getType() != libconfig::Setting::TypeFloat ||
            cone["color"]["g"].getType() != libconfig::Setting::TypeFloat ||
            cone["color"]["b"].getType() != libconfig::Setting::TypeFloat ||
            cone["fuzz"].getType() != libconfig::Setting::TypeFloat) {
                throw errorParser(errorParser::WRONG_TYPE);
            }
        }
        flag++;
    }
    if (_root["primitives"].exists("cubes")) {
        flag++;
    }
    if (_root["primitives"].exists("triangles")) {
        flag++;
    }
    if (_root["primitives"].exists("pyramids")) {
        flag++;
    }
    if (_root["primitives"].exists("planes")) {
        const libconfig::Setting &planes = primitives["planes"];
        for (int i = 0; i < planes.getLength(); i++) {
            const libconfig::Setting &plane = planes[i];
            if (plane["pos"]["x"].getType() != libconfig::Setting::TypeFloat ||
            plane["pos"]["y"].getType() != libconfig::Setting::TypeFloat ||
            plane["pos"]["z"].getType() != libconfig::Setting::TypeFloat ||
            plane["axis"]["x"].getType() != libconfig::Setting::TypeFloat ||
            plane["axis"]["y"].getType() != libconfig::Setting::TypeFloat ||
            plane["axis"]["z"].getType() != libconfig::Setting::TypeFloat ||
            plane["dir"]["x"].getType() != libconfig::Setting::TypeFloat ||
            plane["dir"]["y"].getType() != libconfig::Setting::TypeFloat ||
            plane["dir"]["z"].getType() != libconfig::Setting::TypeFloat ||
            plane["material"].getType() != libconfig::Setting::TypeString ||
            plane["color"]["r"].getType() != libconfig::Setting::TypeFloat ||
            plane["color"]["g"].getType() != libconfig::Setting::TypeFloat ||
            plane["color"]["b"].getType() != libconfig::Setting::TypeFloat) {
                throw errorParser(errorParser::WRONG_TYPE);
            }
        }
        flag++;
    }
    if (_root["primitives"].getLength() > flag) {
        throw errorParser(errorParser::WRONG_NAME);
    }
}
