/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

namespace Raytracer {
    Cylinder3D::Cylinder3D()
    {
        _origin = Math::Point3D();
        _radius = 1;
        _direction = Math::Vector3D();
    }

    Cylinder3D::Cylinder3D(Math::Point3D origin, float radius, Math::Vector3D direction)
    {
        _origin = origin;
        _radius = radius;
        _direction = direction;
        _direction.normalise();
    }

    bool Cylinder3D::intersection(Raytracer::Ray ray, Math::Point3D &point)
    {
        float cDirectionDotRDirection = _direction.dot(ray._direction) /*  direction * transform matrix (rotation) */;
        Math::Point3D RelativePoint = ray._origin - _origin;
        float cDirectionDotRRelative = RelativePoint.dot(_direction) /* Same as above */;

        float a = 1 - ((cDirectionDotRDirection) * (cDirectionDotRDirection));
        float b = 2 * ((RelativePoint.dot(ray._direction)) - (cDirectionDotRDirection * cDirectionDotRRelative));
        float c = (RelativePoint.dot(RelativePoint)) - ((cDirectionDotRRelative) * (cDirectionDotRRelative)) - _radius * _radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
            float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
            float t = 0;
            if (t1 < 0 && t2 >= 0)
                t = t2;
            else if (t1 >= 0 && t2 < 0)
                t = t1;
            else if (t1 < 0 && t2 < 0)
                return false;
            else
                t = (t1 < t2) ? t1 : t2;
            point = ray._origin + ray._direction * t;
            return true;
        }
        return false;
    }

    Math::Vector3D Cylinder3D::getNormal(Math::Point3D &hitPoint, __attribute__((__unused__)) Ray &ray)
    {
        Math::Vector3D originToHit = _origin.vectorise(hitPoint);
        originToHit.normalise();
        Math::Vector3D ortho = originToHit.cross(_direction);
        ortho.normalise();
        Math::Vector3D normal = ortho.cross(_direction);
        normal.normalise();
        float angle = acos(originToHit.dot(normal)) * 180 / M_PI;
        if (angle > 90) {
            return normal * -1;
        }
        return normal;
    }

    void Cylinder3D::scale(Math::Matrix const &matrix)
    {
        Math::Vector3D tmp = Math::Vector3D(_radius, 0, 0);
        tmp = matrix.applyToVector(tmp);
        _radius = tmp._x;
    }

    void Cylinder3D::rotation(Math::Matrix const &matrix)
    {
        _direction = matrix.applyToVector(_direction);
        _direction.normalise();
    }

    void Cylinder3D::translation(Math::Matrix const &matrix)
    {
        _origin = matrix.applyToPoint(_origin);
    }

}
