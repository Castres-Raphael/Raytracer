/*
** EPITECH PROJECT, 2024
** tracer_de_rayon
** File description:
** Matrix
*/

#include "Matrix.hpp"

namespace Math {

    Matrix::Matrix()
    {
        _matrix = {{1, 0, 0, 0},
                   {0, 1, 0, 0},
                   {0, 0, 1, 0},
                   {0, 0, 0, 1}};
    }

    Matrix::Matrix(std::vector<float> l1, std::vector<float> l2, std::vector<float> l3, std::vector<float> l4)
    {
        _matrix.push_back(l1);
        _matrix.push_back(l2);
        _matrix.push_back(l3);
        _matrix.push_back(l4);
    }

    void Matrix::createXRotation(float angle, Matrix &mat)
    {
        float cosAngle = cos(angle * M_PI / 180);
        float sinAngle = sin(angle * M_PI / 180);
        std::vector<float> l1 = {1, 0,        0,         0};
        std::vector<float> l2 = {0, cosAngle, -sinAngle, 0};
        std::vector<float> l3 = {0, sinAngle, cosAngle,  0};
        std::vector<float> l4 = {0, 0,        0,         1};
        Matrix newMat = Matrix(l1, l2, l3, l4);
        mat = newMat;
    }

    void Matrix::createYRotation(float angle, Matrix &mat)
    {
        float cosAngle = cos(angle * M_PI / 180);
        float sinAngle = sin(angle * M_PI / 180);
        std::vector<float> l1 = {cosAngle,  0, sinAngle, 0};
        std::vector<float> l2 = {0,         1, 0,        0};
        std::vector<float> l3 = {-sinAngle, 0, cosAngle, 0};
        std::vector<float> l4 = {0,         0, 0,        1};
        Matrix newMat = Matrix(l1, l2, l3, l4);
        mat = newMat;
    }

    void Matrix::createZRotation(float angle, Matrix &mat)
    {
        float cosAngle = cos(angle * M_PI / 180);
        float sinAngle = sin(angle * M_PI / 180);
        std::vector<float> l1 = {cosAngle, -sinAngle, 0, 0};
        std::vector<float> l2 = {sinAngle, cosAngle,  0, 0};
        std::vector<float> l3 = {0,        0,         1, 0};
        std::vector<float> l4 = {0,        0,         0, 1};
        Matrix newMat = Matrix(l1, l2, l3, l4);
        mat = newMat;
    }

    void Matrix::createTranslation(Vector3D &translation, Matrix &mat)
    {
        std::vector<float> l1 = {1, 0, 0, translation._x};
        std::vector<float> l2 = {0, 1, 0, translation._y};
        std::vector<float> l3 = {0, 0, 1, translation._z};
        std::vector<float> l4 = {0, 0, 0, 1};
        Matrix newMat = Matrix(l1, l2, l3, l4);
        mat = newMat;
    }

    void Matrix::createScale(Vector3D &scale, Matrix &mat)
    {
        std::vector<float> l1 = {scale._x, 0,        0,        0};
        std::vector<float> l2 = {0,        scale._y, 0,        0};
        std::vector<float> l3 = {0,        0,        scale._z, 0};
        std::vector<float> l4 = {0,        0,        0,        1};
        Matrix newMat = Matrix(l1, l2, l3, l4);
        mat = newMat;
    }

    void Matrix::createScale(float scale, Matrix &mat)
    {
        std::vector<float> l1 = {scale, 0,     0,     0};
        std::vector<float> l2 = {0,     scale, 0,     0};
        std::vector<float> l3 = {0,     0,     scale, 0};
        std::vector<float> l4 = {0,     0,     0,     1};
        Matrix newMat = Matrix(l1, l2, l3, l4);
        mat = newMat;
    }

    Vector3D Matrix::applyToVector(Vector3D &vec) const
    {
        float x = _matrix[0][0] * vec._x + _matrix[0][1] * vec._y + _matrix[0][2] * vec._z + _matrix[0][3];
        float y = _matrix[1][0] * vec._x + _matrix[1][1] * vec._y + _matrix[1][2] * vec._z + _matrix[1][3];
        float z = _matrix[2][0] * vec._x + _matrix[2][1] * vec._y + _matrix[2][2] * vec._z + _matrix[2][3];
        return Vector3D(x, y, z);
    }

    Point3D Matrix::applyToPoint(Point3D &point) const
    {
        float x = _matrix[0][0] * point._x + _matrix[0][1] * point._y + _matrix[0][2] * point._z + _matrix[0][3];
        float y = _matrix[1][0] * point._x + _matrix[1][1] * point._y + _matrix[1][2] * point._z + _matrix[1][3];
        float z = _matrix[2][0] * point._x + _matrix[2][1] * point._y + _matrix[2][2] * point._z + _matrix[2][3];
        return Point3D(x, y, z);
    }

    void Matrix::multiplyMatrix(Matrix &matr)
    {
        float result = 0;
        std::vector<std::vector<float>> tmp = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        };

        for (auto i = 0; i < MATRIX_LENGTH; i++) {
            for (std::size_t j = 0; j < MATRIX_LENGTH; j++) {
                for (std::size_t k = 0; j < MATRIX_LENGTH; k++) {
                    result += _matrix[i][k] * matr._matrix[k][j];
                }
                tmp[i][j] = result;
                result = 0;
            }
        }
        _matrix = tmp;
    }
}
