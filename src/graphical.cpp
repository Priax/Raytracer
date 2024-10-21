/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** Graphical lib
*/

#include "graphical.hpp"

Display::Display(const std::size_t width, const std::size_t height,
                std::shared_ptr<std::list<sf::Color>> &colorsQueue,
                std::shared_ptr<std::mutex> &colorsQueueMutex)
{
    _image.create(width, height, sf::Color(0, 0, 0));
    _height = height;
    _width = width;
    _colorsQueue = colorsQueue;
    _colorsQueueMutex = colorsQueueMutex;
}

void Display::updateImage(std::size_t &lastPixelSetX, std::size_t &lastPixelSetY)
{
    std::lock_guard guard(*_colorsQueueMutex);

    if (_colorsQueue->empty())
        return;
    while (!_colorsQueue->empty()) {
        if (lastPixelSetX >= _width) {
            lastPixelSetX = 0;
            lastPixelSetY++;
        }
        if (lastPixelSetY >= _height)
            break;
        _image.setPixel(lastPixelSetX, lastPixelSetY, _colorsQueue->front());
        _colorsQueue->pop_front();
        lastPixelSetX++;
    }
    _imageTexture.update(_image);
    _imageSprite.setTexture(_imageTexture);
}

void Display::displayLoop()
{
    std::size_t lastPixelSetX = 0;
    std::size_t lastPixelSetY = 0;
    bool endLoop = false;


    _renderWindow = std::unique_ptr<sf::RenderWindow>(
        new sf::RenderWindow(sf::VideoMode (_width, _height), "Raytracer Preview", sf::Style::Close|sf::Style::Titlebar));
    if (!_imageTexture.loadFromImage(_image)) {
        std::clog << "error loading image" << std::endl;
        _renderWindow->close();
        return;
    }
    updateImage(lastPixelSetX, lastPixelSetY);
    _refreshClock.restart();
    while (_renderWindow->isOpen()) {
        while (_renderWindow->pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                endLoop = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                endLoop = true;
        }
        if (endLoop)
            break;
        _renderWindow->clear(sf::Color::White);
        _renderWindow->draw(_imageSprite);
        _renderWindow->display();
        _time = _refreshClock.getElapsedTime();
        if (_time.asMilliseconds() < 500)
            continue;
        updateImage(lastPixelSetX, lastPixelSetY);
        _refreshClock.restart();
    }
    _renderWindow->close();
}

int Display::searchGraphicalParam(char **argv, bool &launchPreview, bool &previewLowQuality)
{
    size_t argc;

    for (argc = 0; argv[argc] && argc < 3; argc++);
    if (argc == 2)
        return 0;
    if (argc == 3) {
        std::string param = argv[2];
        if (param.compare("-G--low") == 0) { /*low quality preview*/
            launchPreview = true;
            previewLowQuality = true;
        } else if (param.compare("-G") == 0) { /*-G for --Graphical*/
            launchPreview = true;
        } else {
            std::clog << "Read the documentation for help."<< std::endl;
            return 84;
        }
        return 0;
    }
    std::clog << "Read the documentation for help."<< std::endl;
    return 84;
}

void Display::runPreview(bool &previewLowQuality, camera &realCamera, hittable_list &world, hittable_list &lights)
{
    if (previewLowQuality) {
        std::cout.setstate(std::ios_base::failbit);
        std::clog.setstate(std::ios_base::failbit);
        camera preview = realCamera;
        preview.samples_per_pixel = 10;
        preview._colorsQueue = _colorsQueue;
        preview._colorsQueueMutex = _colorsQueueMutex;
        _previewThread.reset(new std::thread(&camera::render, &preview, std::ref(world), std::ref(lights)));
    } else {
        realCamera._colorsQueue = _colorsQueue;
        realCamera._colorsQueueMutex = _colorsQueueMutex;
    }
    std::thread displayThread(&Display::displayLoop, this);
    if (_previewThread && _previewThread->joinable()) {
        _previewThread->join();
        std::cout.clear();
        std::clog.clear();
    }
    realCamera.render(world, lights);
    displayThread.join();
}
