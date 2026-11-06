/*
** EPITECH PROJECT, 2024
** B-OOP-400-TLS-4-1-raytracer-raphael.castres [WSL: Ubuntu]
** File description:
** Mirror
*/

#pragma once
#include "Definition.hpp"
#include "IMaterial.hpp"

namespace Raytracer {
    class Mirror : public IMaterial
    {
        public:
            Mirror(Color color = Color(255.0f, 255.0f, 255.0f));
            ~Mirror() override = default;

            Ray getBounceRay(Ray prevRay, Math::Vector3D normal, Math::Point3D origin) override;
            Color getEmitedColor() override;

        private:
            Color _color;
    };
}
