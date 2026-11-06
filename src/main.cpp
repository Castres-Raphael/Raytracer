/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main
*/
#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iostream>
#include <optional>
#include "Camera.hpp"
#include "Scene.hpp"
#include "World.hpp"
#include "WorldBuilder.hpp"
#include "World.hpp"

int justPpm(Raytracer::World *warudo, std::string fileName)
{
    for (int i = 0; i < warudo->_nbFrame; i++) {
        warudo->renderWorld();
    }
    warudo->writePPMFile(fileName);
    return 0;
}

int realTimeRender(Raytracer::World *warudo, std::string fileName)
{
    sf::VideoMode customVideoMode({static_cast<unsigned int>(warudo->_x), static_cast<unsigned int>(warudo->_y)});
    sf::RenderWindow window(customVideoMode, "Raytracer");
    sf::Image image({static_cast<unsigned int>(warudo->_x), static_cast<unsigned int>(warudo->_y)}, sf::Color::Black);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                warudo->writePPMFile(fileName);
                return 0;
            }
        }
        warudo->renderWorld();
        warudo->dumpImage(image);
        sf::Texture texture(image);
        sf::Sprite sprite(texture);
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./raytracer [config_file]" << std::endl;
        return 84;
    }

    Raytracer::Scene scene(av[1]);
    Raytracer::WorldBuilder builder;
    scene.setBuilder(&builder);
    scene.BuildWorld();
    Raytracer::World *warudo = builder.getWorld();

    srand(time(NULL));
    if (warudo->_display == false) {
        return justPpm(warudo, av[1]);
    }
    return realTimeRender(warudo, av[1]);
}
