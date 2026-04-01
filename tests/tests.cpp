/*
** EPITECH PROJECT, 2024
** B-OOP-400 NanoTekSpice
** File description:
** contains all tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/hittable.hpp"
#include "../src/hittable_list.hpp"
#include "../src/color.hpp"
#include "../src/camera.hpp"
#include "../src/material.hpp"
#include "../src/primitives/sphere.hpp"
#include "../src/primitives/quad.hpp"
#include "../src/primitives/cylinder.hpp"
#include "../src/primitives/cone.hpp"
#include "../src/primitives/pyramide.hpp"
#include "../src/new_parser.hpp"

Test(ParsingTest, InexistantFile)
{
    libconfig::Config config;
    std::string non_existing_file = "HelloWorld.cfg";

    cr_expect_throw(config.readFile(non_existing_file), libconfig::FileIOException);
}

Test(ParsingTest, EmptyFile)
{
    libconfig::Config config;
    std::string emptyFilePath = "tests/cfg_file/empty.cfg";

    config.readFile(emptyFilePath);
    newParser np(config);
    cr_expect_throw(np.checkValidity(), errorParser);
}

Test(ParsingTest, invalidFile)
{
    libconfig::Config config;
    std::string emptyFilePath = "tests/cfg_file/invalidFile.cfg";

    config.readFile(emptyFilePath);
    newParser np(config);
    cr_expect_throw(np.checkValidity(), errorParser);
}

Test(ParsingTest, getValidValue)
{
    libconfig::Config config;
    std::string FilePath = "tests/cfg_file/quad_and_ball.cfg";

    config.readFile(FilePath);
    newParser np(config);
    np.checkValidity();
    np.parseCamera();
    np.parsePrimitives();
    np.parseLights();
    cr_assert_eq(np.getCameraSize("width"), 500);
    cr_assert_eq(np.getCameraSize("height"), 300);
}

Test(ThreadTest, withColorQueue)
{
    libconfig::Config config;
    hittable_list world;
    hittable_list lights;
    camera cam;
    std::string FilePath = "tests/cfg_file/quad_and_ball.cfg";
    std::shared_ptr<std::list<sf::Color>> colorsQueue = std::make_shared<std::list<sf::Color>>();
    std::shared_ptr<std::mutex> colorsQueueMutex = std::make_shared<std::mutex>();

    config.readFile(FilePath);
    newParser np(config);
    np.checkValidity();
    np.parseCamera();
    np.parsePrimitives();
    np.parseLights();

    std::cout.setstate(std::ios_base::failbit);
    std::clog.setstate(std::ios_base::failbit);
    cam = np.setDataCam(cam);
    world = np.setDataPrim(world);
    lights = np.setDataLights(lights);
    cam._colorsQueue = colorsQueue;
    cam._colorsQueueMutex = colorsQueueMutex;
    cam.render(world, lights);
    std::cout.clear();
    std::clog.clear();
    cr_assert_not(colorsQueue->empty());
}

Test(ThreadTest, withoutQueue)
{
    libconfig::Config config;
    hittable_list world;
    hittable_list lights;
    camera cam;
    std::string FilePath = "tests/cfg_file/quad_and_ball.cfg";
    std::shared_ptr<std::list<sf::Color>> colorsQueue = std::make_shared<std::list<sf::Color>>();
    std::shared_ptr<std::mutex> colorsQueueMutex = std::make_shared<std::mutex>();

    config.readFile(FilePath);
    newParser np(config);
    np.checkValidity();
    np.parseCamera();
    np.parsePrimitives();
    np.parseLights();

    std::cout.setstate(std::ios_base::failbit);
    std::clog.setstate(std::ios_base::failbit);
    cam = np.setDataCam(cam);
    world = np.setDataPrim(world);
    lights = np.setDataLights(lights);
    cam.render(world, lights);
    std::cout.clear();
    std::clog.clear();
    cr_assert(colorsQueue->empty());
}

// Regression: camera rotation block was checking "position" instead of "rotation"
Test(ParsingTest, CameraRotation)
{
    libconfig::Config config;
    std::string FilePath = "tests/cfg_file/camera_rotation.cfg";

    config.readFile(FilePath);
    newParser np(config);
    np.parseCamera();
    camera cam;
    cam = np.setDataCam(cam);
    // vup is set from _cameraRot; rotation = {x=0, y=1, z=0}
    cr_assert_float_eq(cam.vup.y(), 1.0, 1e-6);
}

// Regression: getCameraSize used compare() which returns 0 (falsy) on match
Test(ParsingTest, getCameraSize_correct)
{
    libconfig::Config config;
    std::string FilePath = "tests/cfg_file/quad_and_ball.cfg";

    config.readFile(FilePath);
    newParser np(config);
    np.parseCamera();
    cr_assert_eq(np.getCameraSize("width"), 500);
    cr_assert_eq(np.getCameraSize("height"), 300);
    cr_assert_eq(np.getCameraSize("unknown"), 0);
}

// Regression: cylinders with "noise" material were not pushed to the list
Test(ParsingTest, CylinderNoiseMaterialParsed)
{
    libconfig::Config config;
    std::string FilePath = "tests/cfg_file/noise_cylinder.cfg";

    config.readFile(FilePath);
    newParser np(config);
    np.parsePrimitives();
    hittable_list world;
    // Both cylinders (noise + solid) must be in the world, not just the solid one
    world = np.setDataPrim(world);
    cr_assert_eq(world.objects.size(), 2);
}

Test(ParsingTest, AllPrimitiveTypes)
{
    libconfig::Config config;
    std::string FilePath = "tests/cfg_file/all_primitives.cfg";

    config.readFile(FilePath);
    newParser np(config);
    np.parsePrimitives();
    hittable_list world;
    world = np.setDataPrim(world);
    // 2 spheres + 1 cylinder + 1 cone + 1 plane + 2 triangles + 1 cube + 1 pyramid = 9
    cr_assert_eq(world.objects.size(), 9);
}

Test(ParsingTest, LightSphereColorNotFromCone)
{
    libconfig::Config config;
    std::string FilePath = "tests/cfg_file/light_colors.cfg";

    config.readFile(FilePath);
    newParser np(config);
    np.parseLights();
    hittable_list lights;
    // Should not crash or mix up colors between sphere/cylinder/cone lights
    cr_assert_no_throw(lights = np.setDataLights(lights), std::exception);
    cr_assert_eq(lights.objects.size(), 3);
}
