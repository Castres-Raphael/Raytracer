/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cone
*/

#pragma once

#include "Ray.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "AShape.hpp"

namespace Raytracer {
    class Cone3D : public AShape {
        public:
            Cone3D();
            Cone3D(Math::Point3D origin, float angle, Math::Vector3D direction);
            ~Cone3D() = default;
            bool intersection(Raytracer::Ray ray, Math::Point3D &point) override;
            Math::Vector3D getNormal(Math::Point3D &hitPoint, Ray &ray) override;
            void scale(Math::Matrix const &matrix) override;
            void rotation(Math::Matrix const &matrix) override;
            void translation(Math::Matrix const &matrix) override;

        private:
            IMaterial *_material;
            Math::Vector3D _direction;
            Math::Point3D _origin;
            float _angle;
    };
}
