/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** main
*/

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "primitives/sphere.hpp"
#include "primitives/quad.hpp"
#include "primitives/cylinder.hpp"
#include "primitives/cone.hpp"
#include "primitives/pyramide.hpp"
#include "graphical.hpp"
#include <thread>

#include "new_parser.hpp"

int main(int argc, char **argv)
{
    std::shared_ptr<std::list<sf::Color>> colorsQueue = std::make_shared<std::list<sf::Color>>();
    std::shared_ptr<std::mutex> colorsQueueMutex = std::make_shared<std::mutex>();
    bool launchPreview = false;
    bool previewLowQuality = false;

    if (argc > 3 || Display::searchGraphicalParam(argv, launchPreview, previewLowQuality) == 84)
        return 84;
    libconfig::Config config;
    try {
        config.readFile(argv[1]);
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Could not read the given file\n";
        exit(84);
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
        << " - " << pex.getError() << std::endl;
        exit(84);
    }
    hittable_list world;
    hittable_list lights;
    newParser np(config);
    try {
        np.checkValidity();
        np.parseCamera();
        np.parsePrimitives();
        np.parseLights();
        world = np.setDataPrim(world);
        lights = np.setDataLights(lights);
        camera cam;
        cam = np.setDataCam(cam);
        if (launchPreview) {
            Display display(np.getCameraSize("width"), np.getCameraSize("height"), colorsQueue, colorsQueueMutex);
            display.runPreview(previewLowQuality, cam, world, lights);
        } else {
            cam.render(world, lights);
        }
    } catch (errorParser &e) {
        std::cerr << "Error occured : " << e.what() << std::endl;
        return 84;
    } catch (libconfig::SettingNotFoundException &e) {
        std::cerr << "Incorrect setting " << e.getPath() << std::endl;
        return 84;
    }
    return 0;
}
