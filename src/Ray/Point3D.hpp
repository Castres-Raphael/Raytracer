/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Point3D
*/

#pragma once

#include "Vector3D.hpp"

namespace Math {
    class Point3D {
        public:
            inline Point3D()
            {
                _x = 0;
                _y = 0;
                _z = 0;
            }

            inline Point3D(float x, float y, float z)
            {
                _x = x;
                _y = y;
                _z = z;
            }

            inline float dot(const Point3D &p)
            {
                return _x * p._x + _y * p._y + _z * p._z;
            }

            inline float dot(const Vector3D &v)
            {
                return _x * v._x + _y * v._y + _z * v._z;
            }

            inline Point3D operator+(const Vector3D &v)
            {
                return Point3D(_x + v._x, _y + v._y, _z + v._z);
            }

            inline Point3D operator-(const Vector3D &v)
            {
                return Point3D(_x - v._x, _y - v._y, _z - v._z);
            }

            inline Point3D operator+(const Point3D &p)
            {
                return Point3D(_x + p._x, _y + p._y, _z + p._z);
            }

            inline Point3D operator-(const Point3D &p)
            {
                return Point3D(_x - p._x, _y - p._y, _z - p._z);
            }

            inline Vector3D vectorise(const Point3D &dest)
            {
                return Vector3D(dest._x - _x, dest._y - _y, dest._z - _z);
            }

            float _x;
            float _y;
            float _z;
    };
}
