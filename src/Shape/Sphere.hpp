/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#pragma once

#include "Ray.hpp"
#include "AShape.hpp"
#include "Point3D.hpp"

namespace Raytracer {
    class Sphere : public AShape
    {
        public:
            Sphere();
            Sphere(Math::Point3D center, float radius);
            ~Sphere() override = default;
            bool hits(Ray ray);
            bool intersection(Raytracer::Ray ray, Math::Point3D &point) override;
            void scale(Math::Matrix const &matrix) override;
            void rotation(Math::Matrix const &matrix) override;
            void translation(Math::Matrix const &matrix) override;
            Math::Vector3D getNormal(Math::Point3D &hitPoint, Ray &ray) override;

        private:
            IMaterial *_material;
            Math::Point3D _center;
            float _radius;
    };
}
