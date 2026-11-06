/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rectangle3D
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace Math {
    class Rectangle3D {
        public:
            Rectangle3D();
            Rectangle3D(Point3D origin, Vector3D bottom_side, Vector3D left_side);
            ~Rectangle3D() = default;
            Point3D pointAt(float u, float v);

            Point3D _origin;
            Vector3D _bottom_side;
            Vector3D _left_side;
    };
}
