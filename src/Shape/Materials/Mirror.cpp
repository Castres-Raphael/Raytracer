/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-raphael.castres [WSL: Ubuntu]
** File description:
** Mirror
*/

#include "Mirror.hpp"


namespace Raytracer {

    Mirror::Mirror(Color color)
    {
        _color = color / 255.0f;
    }

    Ray Mirror::getBounceRay(Ray prevRay, Math::Vector3D normal, Math::Point3D origin)
    {
        Ray newRay;

        newRay._color = prevRay._color * _color;
        newRay._origin = origin;
        newRay._direction = prevRay._direction - ((normal * 2) * (prevRay._direction.dot(normal)));
        newRay._direction.normalise();
        return newRay;
    }

    Color Mirror::getEmitedColor()
    {
        return Color(0, 0, 0);
    }
}
