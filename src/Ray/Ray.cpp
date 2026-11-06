/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

namespace Raytracer {

    Ray::Ray()
    {
        _origin = Math::Point3D();
        _direction = Math::Vector3D();
        _color = Color(255, 255, 255);
    }

    Ray::Ray(Math::Point3D origin, Math::Vector3D direction, Color color)
    {
        _origin = origin;
        _direction = direction;
        _color = color;
    }

}