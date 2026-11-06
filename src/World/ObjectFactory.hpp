/*
** EPITECH PROJECT, 2024
** Component
** File description:
** Factory
*/

#pragma once

#include "IShape.hpp"

class ShapeFactory {
    public:
        ShapeFactory() = default;
        ~ShapeFactory() = default;
        
        Raytracer::IShape *createSphere(Math::Point3D origin, float radius);
        Raytracer::IShape *createCylinder(Math::Point3D origin, float radius, Math::Vector3D direction);
        Raytracer::IShape *createTriangle(Math::Point3D p1, Math::Point3D p2, Math::Point3D p3);
        Raytracer::IShape *createPlane(Math::Point3D origin, Math::Vector3D normal);
        Raytracer::IShape *createCone(Math::Point3D origin, float angle, Math::Vector3D direction);

    protected:
    private:
};

class MaterialFactory {
    public:
        MaterialFactory() = default;
        ~MaterialFactory() = default;
        
        Raytracer::IMaterial *createFlat(Color color, float intensity);
        Raytracer::IMaterial *createMirror(Color color);

    protected:
    private:
};
