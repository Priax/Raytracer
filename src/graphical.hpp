/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** Graphical lib
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include <memory>
    #include <list>
    #include <mutex>
    #include <thread>
    #include <atomic>
    #include "camera.hpp"

class Display {
    public:
        Display(const std::size_t width, const std::size_t height,
                std::shared_ptr<std::list<sf::Color>> &colorsQueue,
                std::shared_ptr<std::mutex> &colorsQueueMutex);

        ~Display() = default;

        void updateImage(std::size_t &lastPixelSetX, std::size_t &lastPixelSetY);
        void displayLoop();
        void setWindowHeight(size_t height) {_height = height;};
        void setWindowWidth(size_t width) {_width = width;};

        static int searchGraphicalParam(char **argv, bool &launchPreview, bool &previewLowQuality);
        void runPreview(bool &previewLowQuality, camera &realCamera, hittable_list &world, hittable_list &lights);

        void setCancelRender(std::atomic<bool>* cancel) { _cancel_render = cancel; }

    private:
        std::string _path;
        std::unique_ptr<sf::RenderWindow> _renderWindow;
        sf::Event _event;
        sf::Clock _refreshClock;
        sf::Time _time;
        sf::Image _image;
        sf::Sprite _imageSprite;
        sf::Texture _imageTexture;
        std::size_t _height;
        std::size_t _width;
        std::shared_ptr<std::list<sf::Color>> _colorsQueue = nullptr;
        std::shared_ptr<std::mutex> _colorsQueueMutex = nullptr;
        std::unique_ptr<std::thread> _previewThread = nullptr;
        std::atomic<bool>* _cancel_render = nullptr;
};

#endif /* !SFML_HPP_ */
