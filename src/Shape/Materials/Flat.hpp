/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-raphael.castres [WSL: Ubuntu]
** File description:
** Flat
*/

#pragma once

#include "IMaterial.hpp"
#include "Ray.hpp"
#include <random>

namespace Raytracer {
    class Flat : public IMaterial
    {
        public:
            Flat(Color matColor, float intensity = 0);
            ~Flat() override = default;
            Ray getBounceRay(Ray prevRay, Math::Vector3D normal, Math::Point3D origin) override;
            Color getEmitedColor() override;

        private:
            Color _color;
            Color _emitedColor;
            std::normal_distribution<float> _rdm;
    };
}
