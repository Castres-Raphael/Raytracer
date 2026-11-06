/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-raphael.castres [WSL: Ubuntu]
** File description:
** World
*/

#pragma once

#include <SFML/Graphics/Image.hpp>
#include <cstddef>
#include <vector>
#include <atomic>
#include "IShape.hpp"

namespace Raytracer {
    class Camera;
    class World {
    public:
        World();
        ~World();
        int renderWorld(void);
        void addObj(IShape *obj);
        void addCam(Camera *cam);
        void nextCam();
        void prevCam();
        Color getColor(Ray ray);
        void dumpImage(sf::Image &canva);
        void setNbBouce(std::size_t nbBouce);
        void setNbIteration(std::size_t nbIteration);
        void setSkyBox(Color skyBox);
        void setShapes(std::vector<IShape *> &shapes);
        void setCameras(std::vector<Camera *> &cams);
        void setResolution(int width, int height);
        void writePPMFile(std::string file) const;

        float _nbFrame;
        std::size_t _x;
        std::size_t _y;
        bool _display;

    private:
        IShape *getCollider(Ray ray, Math::Point3D &point);
        void renderPixels(void);
        Color symLight(Ray ray);

        std::vector<IShape *> _obj;
        std::vector<Camera *> _cams;
        std::size_t _camIndex;
        Color _skyBox;
        std::size_t _nbIteration;
        std::size_t _nbBouce;
        float _frame;
        std::vector<Color> _img;
        float _weight;
        std::atomic<std::size_t> _curLine;
    };
}