/*
** EPITECH PROJECT, 2024
** RayTracer [WSL: Ubuntu]
** File description:
** WorldBuilder
*/

#pragma once

#include "Builder.hpp"
#include "Definition.hpp"
#include "IShape.hpp"
#include "World.hpp"
#include <vector>

namespace Raytracer {
    class WorldBuilder : public Builder {
        public:
            WorldBuilder();
            ~WorldBuilder();

            void reset();
            void setResolution(int width, int height) override;
            void setWorldParameters(int bounces = 10, int iterations = 10,
            Color skybox = Math::Vector3D(0, 0, 0), int frames = 10, bool display = false) override;
            void setCameras(std::vector<Camera *> &cams) override;
            void setShapes(std::vector<IShape *> &objs) override;
            World *getWorld();

        protected:
        private:
            World *_world;
    };
}
