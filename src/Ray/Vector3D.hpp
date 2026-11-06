/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Vector3D
*/

#pragma once

#include <cmath>

namespace Math {
    class Vector3D {
        public:

            inline Vector3D(float x = 0, float y = 0, float z = 0) : _x(x), _y(y), _z(z), _indiv(1)
            {}
            ~Vector3D() = default;
            inline float length() { return std::sqrt(_x * _x + _y * _y + _z * _z); }
            inline float dot(const Vector3D &v) { return _x * v._x + _y * v._y + _z * v._z; }

            inline Vector3D operator+(const Vector3D &v) {
                return Vector3D(_x + v._x, _y + v._y, _z + v._z);
            }
            inline Vector3D operator+=(const Vector3D &v) {
                _x += v._x;
                _y += v._y;
                _z += v._z;
                return *this;
            }
            inline Vector3D operator-(const Vector3D &v) {
                return Vector3D(_x - v._x, _y - v._y, _z - v._z);
            }
            inline Vector3D operator-=(const Vector3D &v) {
                _x -= v._x;
                _y -= v._y;
                _z -= v._z;
                return *this;
            }
            inline Vector3D operator*(const Vector3D &v) {
                return Vector3D(_x * v._x, _y * v._y, _z * v._z);
            }
            inline Vector3D operator*=(const Vector3D &v) {
                _x *= v._x;
                _y *= v._y;
                _z *= v._z;
                return *this;
            }
            inline Vector3D operator/(const Vector3D &v) {
                return Vector3D(_x / v._x, _y / v._y, _z / v._z);
            }
            inline Vector3D operator/=(const Vector3D &v) {
                _x /= v._x;
                _y /= v._y;
                _z /= v._z;
                return *this;
            }
            inline Vector3D operator*(const float d) {
                return Vector3D(_x * d, _y * d, _z * d);
            }
            inline Vector3D operator*=(const float d) {
                _x *= d;
                _y *= d;
                _z *= d;
                return *this;
            }
            inline Vector3D operator/(const float d) {
                return Vector3D(_x / d, _y / d, _z / d);
            }
            inline Vector3D operator/=(const float d) {
                _x /= d;
                _y /= d;
                _z /= d;
                return *this;
            }
            inline Vector3D cross(const Vector3D &v) {
                return Vector3D(_y * v._z - _z * v._y, _z * v._x - _x * v._z, _x * v._y - _y * v._x);
            }
            inline float norme(void)
            {
                return std::sqrt(_x * _x + _y * _y + _z * _z);
            }
            inline void normalise()
            {
                float n = norme();

                _x /= n;
                _y /= n;
                _z /= n;
            }
            inline Vector3D moy(Vector3D o)
            {
                Vector3D nVect;

                nVect = *this * _indiv;
                nVect += o * o._indiv;
                nVect._indiv = _indiv + o._indiv;
                nVect /= nVect._indiv;
                return nVect;
            }
            float _x;
            float _y;
            float _z;
            int _indiv;
    };
}
