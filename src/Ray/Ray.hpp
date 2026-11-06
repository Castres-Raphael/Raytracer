/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#pragma once

#include "Point3D.hpp"
#include "Definition.hpp"

namespace Raytracer {
    class Ray {
        public:
            Ray();
            Ray(Math::Point3D origin, Math::Vector3D direction, Color c = Color(255, 255, 255));
            ~Ray() = default;

            Math::Point3D _origin;
            Math::Vector3D _direction;
            Color _color;
    };
}
