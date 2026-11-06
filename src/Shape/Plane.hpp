/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#pragma once

#include "AShape.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class Plane : public AShape
    {
        public:
            Plane();
            Plane(Math::Point3D point, Math::Vector3D normal);
            ~Plane() = default;
            bool intersection(Raytracer::Ray ray, Math::Point3D &point) override;
            Math::Vector3D getNormal(Math::Point3D &hitPoint, Ray &Ray) override;
            void scale(Math::Matrix const &matrix) override;
            void rotation(Math::Matrix const &matrix) override;
            void translation(Math::Matrix const &matrix) override;
        private:
            IMaterial *_material;
            Math::Point3D _point;
            Math::Vector3D _normal;
    };
}

