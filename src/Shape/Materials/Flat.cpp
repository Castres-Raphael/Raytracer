/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-raphael.castres [WSL: Ubuntu]
** File description:
** Flat
*/

#include <random>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include "Flat.hpp"

namespace Raytracer {

    Flat::Flat(Color matColor, float intensity)
    {
        _color = matColor / 255.0f;
        _emitedColor = _color * intensity;
        _rdm = std::normal_distribution<float>(0.0f, 0.5f);
    }

    static thread_local std::default_random_engine generator(std::time(NULL));

    Ray Flat::getBounceRay(Ray prevRay, Math::Vector3D normal, Math::Point3D origin)
    {
        Ray newRay;

        newRay._color = prevRay._color * _color;
        newRay._origin = origin;
        newRay._direction._x = _rdm(generator);
        newRay._direction._y = _rdm(generator);
        newRay._direction._z = _rdm(generator);
        if (normal.dot(newRay._direction) < 0)
            newRay._direction *= -1;
        newRay._direction.normalise();
        return newRay;
    }

    Color Flat::getEmitedColor()
    {
        return _emitedColor;
    }
}
