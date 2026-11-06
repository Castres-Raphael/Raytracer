/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rectangle3D
*/

#include "Rectangle3D.hpp"

namespace Math {

    Rectangle3D::Rectangle3D()
    {
        _origin = Point3D();
        _bottom_side = Vector3D();
        _left_side = Vector3D();
    }

    Rectangle3D::Rectangle3D(Point3D origin, Vector3D bottom_side, Vector3D left_side)
        : _origin(origin), _bottom_side(bottom_side), _left_side(left_side)
    {
    }

    Point3D Rectangle3D::pointAt(float u, float v)
    {
        return _origin + _bottom_side * u + _left_side * v;
    }

}