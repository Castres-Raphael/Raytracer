/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-raphael.castres [WSL: Ubuntu]
** File description:
** IMaterial
*/

#pragma once

#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "Definition.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class IMaterial {
    public:
        virtual ~IMaterial() = default;
        virtual Ray getBounceRay(Ray prevRay, Math::Vector3D normal, Math::Point3D origin) = 0;
        virtual Color getEmitedColor() = 0;
    };
}
