/*
** EPITECH PROJECT, 2024
** tracer_de_rayon
** File description:
** Matrix
*/

#pragma once

#define MATRIX_LENGTH 4

#include "Point3D.hpp"
#include <vector>
#include <Vector3D.hpp>

namespace Math {
    class Matrix {
        public:
            Matrix();
            Matrix(std::vector<float> l1, std::vector<float> l2, std::vector<float> l3, std::vector<float> l4);
            static void createXRotation(float angle, Matrix &mat);
            static void createYRotation(float angle, Matrix &mat);
            static void createZRotation(float angle, Matrix &mat);
            static void createTranslation(Vector3D &translation, Matrix &mat);
            static void createScale(Vector3D &scale, Matrix &mat);
            static void createScale(float scale, Matrix &mat);

            ~Matrix() = default;
            Point3D applyToPoint(Point3D &point) const;
            Vector3D applyToVector(Vector3D &vec) const;
            void multiplyMatrix(Matrix &matr);
        private:
            std::vector<std::vector<float>> _matrix;
    };
}

