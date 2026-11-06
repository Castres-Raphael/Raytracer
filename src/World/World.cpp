/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-raphael.castres [WSL: Ubuntu]
** File description:
** World
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <thread>
#include "Camera.hpp"
#include <cstring>
#include <vector>
#include "World.hpp"
#include "Ray.hpp"
#include "Point3D.hpp"
#include "IMaterial.hpp"
#include "IShape.hpp"

namespace Raytracer {
    World::World()
    {
        _display = false;
        _camIndex = 0;
        _frame = 0;
        _x = 1000;
        _y = 1000;
        _img = std::vector<Color>(_x * _y, Color());
        _curLine = 0;
        _weight = 1.0f;
    }

    World::~World()
    {
    }

    IShape *World::getCollider(Ray ray, Math::Point3D &point)
    {
        float min = -1.0f;
        Math::Point3D minPoint;
        IShape *minShape = nullptr;
        std::size_t size = _obj.size();
        Math::Point3D hit;

        for (std::size_t i = 0; i < size && min != 0.0f; i++) {
            if (_obj[i]->intersection(ray, hit)) {
                float n = std::pow(hit._x - ray._origin._x, 2.0f) + std::pow(hit._y - ray._origin._y, 2.0f) + std::pow(hit._z - ray._origin._z, 2.0f);
                if (min < 0.0f || min > n) {
                    min = n;
                    minPoint = hit;
                    minShape = _obj[i];
                }
            }
        }
        point = minPoint;
        return minShape;
    }

    Color World::symLight(Ray ray)
    {
        Color color(0.0f, 0.0f, 0.0f);
        Color emited;
        Math::Point3D hitpoint;
        IShape *shape = nullptr;
        IMaterial *mat = nullptr;
        std::size_t i = 0;

        for (i = 0; i < _nbBouce; i++) {
            shape = getCollider(ray, hitpoint);

            mat = nullptr;

            if (shape != nullptr) {
                mat = shape->getMaterial();
                emited = mat->getEmitedColor();
            } else {
                emited = _skyBox;
            }
            color += emited * ray._color;
            if (emited.dot(emited) > 0.0f || mat == nullptr) {
                break;
            }
            ray = mat->getBounceRay(ray, shape->getNormal(hitpoint, ray), hitpoint);
        }
        return color;
    }

    Color World::getColor(Ray ray)
    {
        Color newColor;
        Color color;

        ray._direction.normalise();
        for (std::size_t i = 0; i < _nbIteration; i++) {
            newColor = symLight(ray);
            color += newColor / _nbIteration;
        }
        return color;
    }

    void World::renderPixels(void)
    {
        Camera *cam = _cams[_camIndex];
        std::size_t myLine = 0;
        float myPercentX = 0;
        float myPercentY = 0;
        float pY = 1 / (float) _y;
        Color color;
        Color prevColor;

        while (_curLine != _x) {
            myLine = _curLine.fetch_add(1);
            myPercentX = myLine / (float)_x;
            myPercentY = 0.0f;
            auto idx = _img.begin() + (myLine * _y);
            for (std::size_t y = 0; y < _y; y++) {
                prevColor = *idx;
                color = cam->ray(myPercentX, myPercentY, *this, _x, _y);
                color = (color * _weight) + (prevColor * (1 - _weight));
                *idx = color;
                myPercentY += pY;
                idx++;
            }
        }
    }

    int World::renderWorld(void)
    {
        if (_cams.size() == 0)
            return 84;
        if (_frame == _nbFrame)
            return 0;
        _weight = 1.0f / (_frame + 1);

        std::vector<std::thread> threads;
        unsigned int max = std::thread::hardware_concurrency();
        _curLine = 0;

        for (unsigned int i = 0; i < max; i++) {
            threads.push_back(std::thread(&World::renderPixels, this));
        }
        for (unsigned int i = 0; i < max; i++) {
            threads[i].join();
        }
        threads.clear();
        _frame++;
        return 0;
    }

    void World::writePPMFile(std::string name) const
    {
        std::ofstream output(name.replace(name.rfind('.'), name.size(), "") + ".ppm");

        output << "P3" << std::endl;
        output << _x << " " << _y << std::endl;
        output << "255" << std::endl;
        for (std::size_t i = 0; i < _y; i++) {
            for (std::size_t j = 0; j < _x; j++) {
                int r = std::clamp(_img.at(j * _y + i)._x * 255.0f, 0.0f, 255.0f);
                int g = std::clamp(_img.at(j * _y + i)._y * 255.0f, 0.0f, 255.0f);
                int b = std::clamp(_img.at(j * _y + i)._z * 255.0f, 0.0f, 255.0f);
                output << r << " " << g << " " << b << std::endl;
            }
        }
    }

    void World::nextCam()
    {
        _camIndex++;
        if (_camIndex >= _cams.size())
            _camIndex = 0;
    }

    void World::prevCam()
    {
        if (_camIndex == 0)
            _camIndex = _cams.size() - 1;
        else
            _camIndex--;
    }

    void World::dumpImage(sf::Image &canva)
    {
        sf::Vector2u size = canva.getSize();
        for (std::size_t i = 0; i < size.x && i < _x; i++) {
            for (std::size_t j = 0; j < size.y && j < _y; j++) {
                canva.setPixel(sf::Vector2u(i, j), sf::Color(std::clamp(_img[i * _y + j]._x * 255.0f, 0.0f, 255.0f),
                                               std::clamp(_img[i * _y + j]._y * 255.0f, 0.0f, 255.0f),
                                               std::clamp(_img[i * _y + j]._z * 255.0f, 0.0f, 255.0f)));
            }
        }
    }

    void World::setCameras(std::vector<Camera *> &cams)
    {
        _cams = cams;
    }

    void World::setShapes(std::vector<IShape *> &shapes)
    {
        _obj = shapes;
    }

    void World::setResolution(int width, int height)
    {
        _x = width;
        _y = height;
    }

    void World::setNbBouce(std::size_t nbBouce)
    {
        _nbBouce = nbBouce;
    }

    void World::setNbIteration(std::size_t nbIteration)
    {
        _nbIteration = nbIteration;
    }

    void World::setSkyBox(Color skyBox)
    {
        _skyBox = skyBox;
    }
}