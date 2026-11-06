/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Shape
*/

#include "AShape.hpp"

namespace Raytracer {

    void AShape::setMaterial(IMaterial *material)
    {
        _material = material;
    }

    IMaterial *AShape::getMaterial(void)
    {
        return _material;
    }

    std::vector<Math::Matrix> &AShape::getTransformation(void)
    {
        return _transformation;
    }

    void AShape::addTransformation(Math::Matrix &newMatrix)
    {
        _transformation.push_back(newMatrix);
    }
}