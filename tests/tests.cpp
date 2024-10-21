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
