/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Triangle
*/

#include "Triangle.hpp"

namespace Raytracer {
    Triangle::Triangle()
    {
        _a = Math::Point3D();
        _b = Math::Point3D();
        _c = Math::Point3D();
        Math::Vector3D u = _a.vectorise(_b);
        Math::Vector3D v = _a.vectorise(_c);
        _normal = u.cross(v);
    }

    Triangle::Triangle(Math::Point3D a, Math::Point3D b, Math::Point3D c) : _a(a), _b(b), _c(c)
    {
        Math::Vector3D u = _a.vectorise(_b);
        Math::Vector3D v = _a.vectorise(_c);
        _normal = u.cross(v);
    }

    bool Triangle::intersection(Raytracer::Ray ray, Math::Point3D &point)
    {
        Math::Vector3D edge1(_b._x - _a._x, _b._y - _a._y, _b._z - _a._z);
        Math::Vector3D edge2(_c._x - _a._x, _c._y - _a._y, _c._z - _a._z);
        Math::Vector3D h = ray._direction.cross(edge2);
        float a = edge1.dot(h);
        if (a > -0.00001 && a < 0.00001)
            return false;
        float f = 1 / a;
        Math::Vector3D s(ray._origin._x - _a._x, ray._origin._y - _a._y, ray._origin._z - _a._z);
        float u = f * s.dot(h);
        if (u < 0 || u > 1)
            return false;
        Math::Vector3D q = s.cross(edge1);
        float v = f * ray._direction.dot(q);
        if (v < 0 || u + v > 1)
            return false;
        float t = f * edge2.dot(q);
        if (t > 0.00001) {
            point = Math::Point3D(ray._origin._x + t * ray._direction._x, ray._origin._y + t * ray._direction._y, ray._origin._z + t * ray._direction._z);
            return true;
        }
        return false;
    }

    Math::Vector3D Triangle::getNormal(UNUSED Math::Point3D &hitPoint, UNUSED Ray &ray)
    {
        return _normal;
    }

    void Triangle::scale(Math::Matrix const &matrix)
    {
        Math::Vector3D abVec = _a.vectorise(_b);
        Math::Vector3D acVec = _a.vectorise(_c);
        abVec = matrix.applyToVector(abVec);
        acVec = matrix.applyToVector(acVec);
        _b = _a + abVec;
        _c = _a + acVec;
    }

    void Triangle::rotation(Math::Matrix const &matrix)
    {
        Math::Vector3D abVec = _a.vectorise(_b);
        Math::Vector3D acVec = _a.vectorise(_c);
        abVec = matrix.applyToVector(abVec);
        acVec = matrix.applyToVector(acVec);
        _b = _a + abVec;
        _c = _a + acVec;
        _normal = abVec.cross(acVec);
    }

    void Triangle::translation(Math::Matrix const &matrix)
    {
        _a = matrix.applyToPoint(_a);
        _b = matrix.applyToPoint(_b);
        _c = matrix.applyToPoint(_c);
    }
}