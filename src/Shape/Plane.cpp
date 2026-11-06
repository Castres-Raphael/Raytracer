/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#include "Plane.hpp"

namespace Raytracer {

    Plane::Plane()
    {
        _normal = Math::Vector3D();
        _point = Math::Point3D();
    }

    Plane::Plane(Math::Point3D point, Math::Vector3D normal)
    {
        _point = point;
        _normal = normal;
    }

    bool Plane::intersection(Raytracer::Ray ray, Math::Point3D &p)
    {
        std::vector<Math::Point3D> r;
        Math::Vector3D rayDir = ray._direction;
        Math::Vector3D rayOrigin = Math::Vector3D(ray._origin._x, ray._origin._y, ray._origin._z);
        Math::Vector3D normal = _normal;
        Math::Vector3D point = Math::Vector3D(_point._x, _point._y, _point._z);
        float t = (point - rayOrigin).dot(normal) / rayDir.dot(normal);
        if (t > 0.00001) {
            p = Math::Point3D(rayOrigin._x + rayDir._x * t, rayOrigin._y + rayDir._y * t, rayOrigin._z + rayDir._z * t);
            return true;
        }
        return false;
    }

    Math::Vector3D Plane::getNormal(__attribute__((__unused__)) Math::Point3D &hitPoint, __attribute__((__unused__)) Ray &ray)
    {
        return _normal;
    }

    void Plane::scale(__attribute__((__unused__)) Math::Matrix const &matrix)
    {
        return;
    }

    void Plane::rotation(Math::Matrix const &matrix)
    {
        _normal = matrix.applyToVector(_normal);
    }

    void Plane::translation(Math::Matrix const &matrix)
    {
        _point = matrix.applyToPoint(_point);
    }
}
