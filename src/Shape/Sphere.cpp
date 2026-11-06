/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace Raytracer {

    Sphere::Sphere()
    {
        _center = Math::Point3D();
        _radius = 0;
    }

    Sphere::Sphere(Math::Point3D center, float radius)
        : _center(center), _radius(radius)
    {
    }

    bool Sphere::hits(Ray ray)
    {
        Math::Vector3D oc(ray._origin._x - _center._x, ray._origin._y - _center._y, ray._origin._z - _center._z);
        float a = ray._direction.dot(ray._direction);
        float b = 2.0 * oc.dot(ray._direction);
        float c = oc.dot(oc) - _radius * _radius;
        float discriminant = b * b - 4 * a * c;
        return (discriminant >= 0);
    }

    bool Sphere::intersection(Ray ray, Math::Point3D &point)
    {
        Math::Vector3D oc = _center.vectorise(ray._origin);
        float a = ray._direction.dot(oc);
        float discriminant = a * a - (oc.dot(oc) - _radius * _radius);
        if (discriminant < 0)
            return false;
        float s = 1;
        if (a > discriminant)
            s = -1;
        if (a < 0)
            s *= -1;
        float t = -a + std::sqrt(discriminant) * s;
        if (t <= 0)
            return false;
        point = ray._origin + ray._direction * t;
        return true;
    }

    Math::Vector3D Sphere::getNormal(Math::Point3D &hitPoint, __attribute__((__unused__)) Ray &ray)
    {
        return _center.vectorise(hitPoint);
    }

    void Sphere::scale(Math::Matrix const &matrix)
    {
        Math::Vector3D tmp = Math::Vector3D(_radius, 0, 0);
        tmp = matrix.applyToVector(tmp);
        _radius = tmp._x;
    }

    void Sphere::rotation(__attribute__((__unused__)) Math::Matrix const &matrix)
    {
        return;
    }

    void Sphere::translation(Math::Matrix const &matrix)
    {
        _center = matrix.applyToPoint(_center);
    }

}
