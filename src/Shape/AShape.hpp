/*
** EPITECH PROJECT, 2024
** tracer_de_rayon
** File description:
** AShape
*/

#pragma once

#include "IShape.hpp"
#include <vector>

namespace Raytracer {
    class AShape : public IShape {
        public:
            virtual ~AShape() = default;
            virtual bool intersection(Raytracer::Ray ray, Math::Point3D &point) = 0;
            virtual Math::Vector3D getNormal(Math::Point3D &hitPoint, Ray &ray) = 0;
            virtual void setMaterial(IMaterial *material) final;
            virtual IMaterial *getMaterial(void) final;
            virtual std::vector<Math::Matrix> &getTransformation(void) final;
            virtual void addTransformation(Math::Matrix &newMatrix) final;
            virtual void scale(Math::Matrix const &matrix) = 0;
            virtual void rotation(Math::Matrix const &matrix) = 0;
            virtual void translation(Math::Matrix const &matrix) = 0;

        protected:
            IMaterial *_material;
            std::vector<Math::Matrix> _transformation;
    };
}
