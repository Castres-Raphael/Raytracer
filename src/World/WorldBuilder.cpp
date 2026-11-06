/*
** EPITECH PROJECT, 2024
** RayTracer [WSL: Ubuntu]
** File description:
** WorldBuilder
*/

#include "WorldBuilder.hpp"

namespace Raytracer {
    WorldBuilder::WorldBuilder()
    {
        this->reset();
    }

    WorldBuilder::~WorldBuilder()
    {
        delete _world;
    }

    void WorldBuilder::reset()
    {
        this->_world = new World();
    }

    void WorldBuilder::setResolution(int width, int height)
    {
        _world->setResolution(width, height);
    }

    void WorldBuilder::setWorldParameters(int bounces, int iterations, Color skybox, int frames, bool display)
    {
        _world->setNbBouce(bounces);
        _world->setNbIteration(iterations);
        _world->setSkyBox(skybox);
        _world->_display = display;
        _world->_nbFrame = frames;
    }

    void WorldBuilder::setCameras(std::vector<Camera *> &cams)
    {
        _world->setCameras(cams);
    }

    void WorldBuilder::setShapes(std::vector<IShape *> &shapes)
    {
        _world->setShapes(shapes);
    }

    World *WorldBuilder::getWorld()
    {
        World *world = _world;
        this->reset();
        return world;
    }
}