/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cone
*/

#include "Cone.hpp"

namespace Raytracer {

    Cone3D::Cone3D()
    {
        _origin = Math::Point3D();
        _angle = 1;
        _direction = Math::Vector3D();
    }

    Cone3D::Cone3D(Math::Point3D origin, float angle, Math::Vector3D direction)
    {
        _origin = origin;
        _angle = angle * M_PI / 180;
        _direction = direction;
        _direction.normalise();
    }

    bool Cone3D::intersection(Raytracer::Ray ray, Math::Point3D &point)
    {
        float cDirectionDotRDirection = _direction.dot(ray._direction);
        Math::Point3D RelativePoint = ray._origin - _origin;
        float cDirectionDotRRelative = RelativePoint.dot(_direction);

        float a = (cDirectionDotRDirection * cDirectionDotRDirection) - (cos(_angle) * cos(_angle));
        float b = 2 * (cDirectionDotRDirection * (cDirectionDotRRelative) - RelativePoint.dot(ray._direction) * (cos(_angle) * cos(_angle)));
        float c = (cDirectionDotRRelative * cDirectionDotRRelative) - RelativePoint.dot(RelativePoint) * cos(_angle) * cos(_angle);
        float discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
            Math::Point3D hit = ray._origin + ray._direction * t1;
            if ((_origin.vectorise(hit).dot(_direction)) < 0) {
                t1 = -1;
            }

            float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
            hit = ray._origin + ray._direction * t2;
            if ((_origin.vectorise(hit).dot(_direction)) < 0) {
                t2 = -1;
            }

            float t = 0;
            if (t1 < 0 && t2 >= 0)
                t = t2;
            else if (t1 >= 0 && t2 < 0)
                t = t1;
            else if (t1 < 0 && t2 < 0)
                return false;
            else
                t = (t1 < t2) ? t1 : t2;
            Math::Point3D hit1 = ray._origin + ray._direction * t;
            if ((_origin.vectorise(hit1).dot(_direction)) > 0) {
                point = hit1;
                return true;
            }
            return false;
        }
        return false;
    }

    Math::Vector3D Cone3D::getNormal(Math::Point3D &hitPoint, __attribute__((__unused__)) Ray &ray)
    {
        Math::Vector3D hitVector = hitPoint.vectorise(_origin);
        Math::Point3D orthoProj = _origin + (_direction * hitVector.dot(_direction) / _direction.dot(_direction));
        Math::Vector3D perp = hitPoint.vectorise(orthoProj);
        Math::Vector3D tangent = hitVector.cross(perp);
        Math::Vector3D normal = tangent.cross(hitVector);
        return normal;
    }

    void Cone3D::scale(Math::Matrix const &matrix)
    {
        Math::Vector3D tmp = Math::Vector3D(_angle * 180 / M_PI, 0, 0);
        tmp = matrix.applyToVector(tmp);
        _angle = tmp._x * M_PI / 180;
    }

    void Cone3D::rotation(Math::Matrix const &matrix)
    {
        _direction = matrix.applyToVector(_direction);
        _direction.normalise();
    }

    void Cone3D::translation(Math::Matrix const &matrix)
    {
        _origin = matrix.applyToPoint(_origin);
    }
}
