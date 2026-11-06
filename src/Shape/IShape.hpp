/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Shape
*/

#pragma once

#include "Point3D.hpp"
#include "Ray.hpp"
#include "IMaterial.hpp"
#include "Matrix.hpp"
#include <vector>

namespace Raytracer {
    class IShape {
    public:
        virtual ~IShape() = default;
        virtual bool intersection(Raytracer::Ray ray, Math::Point3D &point) = 0;
        virtual Math::Vector3D getNormal(Math::Point3D &hitPoint, Ray &ray) = 0;
        virtual void setMaterial(IMaterial *material) = 0;
        virtual IMaterial *getMaterial(void) = 0;
        virtual std::vector<Math::Matrix> &getTransformation(void) = 0;
        virtual void addTransformation(Math::Matrix &newMatrix) = 0;
        virtual void scale(Math::Matrix const &matrix) = 0;
        virtual void rotation(Math::Matrix const &matrix) = 0;
        virtual void translation(Math::Matrix const &matrix) = 0;
    };
}
