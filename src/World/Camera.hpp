/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Rectangle3D.hpp"
#include "World.hpp"

namespace Raytracer {
    class World;
    class Camera {
        public:
            Camera();
            Camera(Math::Rectangle3D origin, Math::Rectangle3D screen, bool antiAlisaing, bool depth);
            ~Camera() = default;
            Color ray(float u, float v, Raytracer::World &world, int sceen_width, int screen_height);

            void move(Math::Vector3D move) {_origin._origin = _origin._origin + move;
                                            _screen._origin = _screen._origin + move;}
        private:
            Math::Rectangle3D _origin;
            Math::Rectangle3D _screen;
            bool _antiAliasing;
            bool _depthField;
    };
}
