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
#include <filesystem>
#include <atomic>
#include <chrono>

#include "new_parser.hpp"

int main(int argc, char **argv)
{
    bool launchPreview = false;
    bool previewLowQuality = false;

    if (argc > 3 || Display::searchGraphicalParam(argv, launchPreview, previewLowQuality) == 84)
        return 84;

    std::string config_file = argv[1];
    std::atomic<bool> cancel_render{false};
    std::atomic<bool> window_is_open{true};

    std::thread watcher([&]() {
        try {
            auto last_time = std::filesystem::last_write_time(config_file);
            while (window_is_open) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                try {
                    auto current_time = std::filesystem::last_write_time(config_file);
                    if (current_time != last_time) {
                        last_time = current_time;
                        cancel_render = true;
                    }
                } catch (...) {}
            }
        } catch (...) {}
    });

    bool first_run = true;

    while (window_is_open) {
        cancel_render = false;
        std::shared_ptr<std::list<sf::Color>> colorsQueue = std::make_shared<std::list<sf::Color>>();
        std::shared_ptr<std::mutex> colorsQueueMutex = std::make_shared<std::mutex>();

        libconfig::Config config;
        try {
            config.readFile(config_file.c_str());
        } catch (const libconfig::FileIOException &fioex) {
            if (first_run) { std::cerr << "Could not read the given file\n"; exit(84); }
            else { std::this_thread::sleep_for(std::chrono::milliseconds(500)); continue; }
        } catch (const libconfig::ParseException &pex) {
            if (first_run) { 
                std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl; exit(84); 
            } else { 
                std::cerr << "\r\033[31mParse error line " << pex.getLine() << " - Waiting for fix...\033[0m\033[K"; 
                std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
                continue; 
            }
        }

        try {
            hittable_list world;
            hittable_list lights;
            newParser np(config);
            np.checkValidity();
            np.parseCamera();
            np.parsePrimitives();
            np.parseLights();
            world = np.setDataPrim(world);
            world = np.setDataModels(world);
            world = np.setDataParametrics(world);
            lights = np.setDataLights(lights);
            camera cam;
            cam = np.setDataCam(cam);
            cam.cancel_render = &cancel_render;

            if (launchPreview) {
                Display display(np.getCameraSize("width"), np.getCameraSize("height"), colorsQueue, colorsQueueMutex);
                display.setCancelRender(&cancel_render);
                display.runPreview(previewLowQuality, cam, world, lights);
            } else {
                cam.render(world, lights);
            }
        } catch (errorParser &e) {
            if (first_run) { std::cerr << "Error occured: " << e.what() << std::endl; exit(84); }
            else { std::this_thread::sleep_for(std::chrono::milliseconds(500)); continue; }
        } catch (libconfig::SettingNotFoundException &e) {
            if (first_run) { std::cerr << "Incorrect setting " << e.getPath() << std::endl; exit(84); }
            else { std::this_thread::sleep_for(std::chrono::milliseconds(500)); continue; }
        }

        if (!cancel_render) {
            window_is_open = false; 
        } else {
            std::clog << "\n\033[33m[!] Modification détectée ! Rechargement de la scène...\033[0m\n";
        }
        first_run = false;
    }

    watcher.join();
    return 0;
}
