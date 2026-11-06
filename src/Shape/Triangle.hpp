/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Triangle
*/

#pragma once

#include "AShape.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"

#define UNUSED __attribute__((unused))

namespace Raytracer {
    class Triangle : public AShape
    {
        public:
            Triangle();
            Triangle(Math::Point3D a, Math::Point3D b, Math::Point3D c);
            ~Triangle() override = default;
            bool intersection(Raytracer::Ray ray, Math::Point3D &point) override;
            Math::Vector3D getNormal(UNUSED Math::Point3D &hitPoint,UNUSED Ray &ray) override;
            void scale(Math::Matrix const &matrix) override;
            void rotation(Math::Matrix const &matrix) override;
            void translation(Math::Matrix const &matrix) override;

        private:
            IMaterial *_material;
            Math::Point3D _a;
            Math::Point3D _b;
            Math::Point3D _c;
            Math::Vector3D _normal;
    };
}

