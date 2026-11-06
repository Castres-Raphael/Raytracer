/*
** EPITECH PROJECT, 2024
** RayTracer [WSL: Ubuntu]
** File description:
** Builder
*/

#pragma once

#include "Definition.hpp"
#include "IShape.hpp"
#include <vector>

namespace Raytracer {
    class Camera;
    class Builder {
        public:
            ~Builder() = default;

            virtual void setResolution(int width, int height) = 0;
            virtual void setWorldParameters(int bounces, int iterations, Color skybox, int frames, bool display) = 0;
            virtual void setCameras(std::vector<Raytracer::Camera *> &) = 0;
            virtual void setShapes(std::vector<Raytracer::IShape *> &) = 0;

        protected:
        private:
    };
}
