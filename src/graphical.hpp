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
    #include <iostream>
    #include <thread>
    #include "camera.hpp"

class Display{
    public:
        /**
         * @brief Create the window
         *
         * @param width the width of the window
         * @param height the height of the window
         * @param colorsQueue list of colors to add to the image
         * @param colorsQueueMutex mutex to avoid unexpected behaviors
        */
        Display(const std::size_t width, const std::size_t height,
                std::shared_ptr<std::list<sf::Color>> &colorsQueue,
                std::shared_ptr<std::mutex> &colorsQueueMutex);

        /**
         * @brief Destroy the window and it's content
         *
         * @param none
        */
        ~Display() = default;

        /**
         * @brief display loop
         *
         * @param lastPixelSetX last pixel set on X axe
         * @param lastPixelSetY last pixel set on Y axe
         * @param lastLineRead last line of the file read
        */
        void updateImage(std::size_t &lastPixelSetX, std::size_t &lastPixelSetY);

        /**
         * @brief display loop
         *
         * @param none
        */
        void displayLoop();

        /**
         * @brief Set window height
         *
         * @param height Window height
        */
        void setWindowHeight(size_t height) {_height = height;};

        /**
         * @brief Set window Width
         *
         * @param width Window Width
        */
        void setWindowWidth(size_t width) {_width = width;};

        /**
         * @brief Check if the program is launched with graphical param
         *
         * @param argv Parameters
         * @param launchPreview Bool set to true when a preview is expected
         * @param previewLowQuality Bool set to true if a preview is expected with low quality
         * @return 84 if error, otherwise 0
        */
        static int searchGraphicalParam(char **argv, bool &launchPreview, bool &previewLowQuality);

        /**
         * @brief Setup the preview
         *
         * @param previewLowQuality Bool set to true if a preview is expected with low quality
         * @param camera object containing all settings for the camera
         * @param world object containing all elements to draw
         * @param lights object containings lights
        */
        void runPreview(bool &previewLowQuality, camera &realCamera, hittable_list &world, hittable_list &lights);

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
};

#endif /* !SFML_HPP_ */
