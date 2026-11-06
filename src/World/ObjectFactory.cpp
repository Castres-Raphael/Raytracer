/*
** EPITECH PROJECT, 2024
** RayTracer [WSL: Ubuntu]
** File description:
** ObjectFactory
*/

#include "ObjectFactory.hpp"
#include "IMaterial.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"
#include "Triangle.hpp"
#include "Cone.hpp"
#include "Flat.hpp"
#include "Mirror.hpp"

Raytracer::IShape *ShapeFactory::createSphere(Math::Point3D origin, float radius)
{
    return new Raytracer::Sphere(origin, radius);
}

Raytracer::IShape *ShapeFactory::createCylinder(Math::Point3D origin, float radius, Math::Vector3D direction)
{
    return new Raytracer::Cylinder3D(origin, radius, direction);
}

Raytracer::IShape *ShapeFactory::createTriangle(Math::Point3D p1, Math::Point3D p2, Math::Point3D p3)
{
    return new Raytracer::Triangle(p1, p2, p3);
}

Raytracer::IShape *ShapeFactory::createPlane(Math::Point3D origin, Math::Vector3D normal)
{
    return new Raytracer::Plane(origin, normal);
}

Raytracer::IShape *ShapeFactory::createCone(Math::Point3D origin, float angle, Math::Vector3D direction)
{
    return new Raytracer::Cone3D(origin, angle, direction);
}

Raytracer::IMaterial *MaterialFactory::createFlat(Color color, float intensity)
{
    return new Raytracer::Flat(color, intensity);
}

Raytracer::IMaterial *MaterialFactory::createMirror(Color color)
{
    return new Raytracer::Mirror(color);
}