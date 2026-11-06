/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#include "Camera.hpp"
#include <cmath>

namespace Raytracer
{
    Camera::Camera()
    {
        _origin = Math::Rectangle3D(Math::Point3D(-0.5, -0.5, 0), Math::Vector3D(1, 0, 0), Math::Vector3D(0, 1, 0));
        _screen = Math::Rectangle3D(Math::Point3D(-0.5, -0.5, 1), Math::Vector3D(1, 0, 0), Math::Vector3D(0, 1, 0));
        _antiAliasing = false;
        _depthField = false;
    }

    Camera::Camera(Math::Rectangle3D origin, Math::Rectangle3D screen, bool antiAlisaing, bool depth)
    {
        _origin = origin;
        _screen = screen;
        _antiAliasing = antiAlisaing;
        _depthField = depth;
    }

    Color Camera::ray(float u, float v, World &world, int screen_width, int screen_height)
    {
        Ray currRay;
        Math::Point3D target;
        Math::Vector3D color;

        if (_antiAliasing == false) {
            target = _screen.pointAt(u, v);
            currRay._origin = _origin.pointAt(0.5, 0.5);
            currRay._direction = currRay._origin.vectorise(target);
            currRay._color = Color(1, 1, 1);
            color = world.getColor(currRay);
        } else {
            float xDeviation = 0;
            float yDeviation = 0;
            float xDeviationTarget = 0;
            float yDeviationTarget = 0;
            float angle = 0;
            for (int i = 0; i < 10; i++) {
                angle = (static_cast<float>(rand() % 1001) / 1000) * 2 * M_PI;
                xDeviationTarget = ((cos(angle) * std::sqrt(static_cast<float>(rand() % 1001) / 1000)) / screen_width) * 0.2;
                /* the value 0.2 correspond to the strength, increase it to make thing more blurry (It will increase the deviation of the ray)*/
                yDeviationTarget = ((sin(angle) * std::sqrt(static_cast<float>(rand() % 1001) / 1000)) / screen_height) * 0.2;
                xDeviation = ((cos(angle) * std::sqrt(static_cast<float>(rand() % 1001) / 1000)) / screen_width) * 20;
                /* the value 20 correspond to the strength, increase it to make thing more blurry (It will increase the deviation of the ray)*/
                yDeviation = ((sin(angle) * std::sqrt(static_cast<float>(rand() % 1001) / 1000)) / screen_height) * 20;
                target = _screen.pointAt(u + xDeviationTarget, v + yDeviationTarget);
                currRay._origin = _origin.pointAt(0.5 + xDeviation * _depthField, 0.5 + yDeviation * _depthField);
                currRay._direction = currRay._origin.vectorise(target);
                currRay._color = Color(1, 1, 1);
                color += world.getColor(currRay);
            }
            color /= 10;
        }
        return color;
    }
}
