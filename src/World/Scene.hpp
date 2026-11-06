/*
** EPITECH PROJECT, 2024
** RayTracer [WSL: Ubuntu]
** File description:
** Scene
*/

#pragma once

#include "Builder.hpp"
#include "Camera.hpp"
#include "IMaterial.hpp"
#include "IShape.hpp"
#include "Matrix.hpp"
#include "Vector3D.hpp"
#include "ObjectFactory.hpp"
#include <libconfig.h++>
#include <SFML/Graphics/Image.hpp>
#include <map>
#include <string>

namespace Raytracer {
    class Scene {
        public:
            Scene(char *filename);
            ~Scene();

            class ParseError : public std::exception {
                public:
                    ParseError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }

                private:
                    std::string _message;
            };

            class TypeError : public std::exception {
                public:
                    TypeError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }

                private:
                    std::string _message;
            };

            class FileNotFound : public std::exception {
                public:
                    FileNotFound(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }

                private:
                    std::string _message;
            };

            Math::Point3D GetPoint3D(const libconfig::Setting &setting) { return Math::Point3D(setting[0], setting[1], setting[2]); }
            Math::Vector3D GetVector3D(const libconfig::Setting &setting) { return Math::Vector3D(setting[0], setting[1], setting[2]); }
            Math::Matrix GetTranslationMatrix(const libconfig::Setting &setting);
            Math::Matrix GetScaleMatrix(const libconfig::Setting &setting);
            Math::Matrix GetRotationMatrix(float angle, std::string axis);
            void ApplyShapeOptions(const libconfig::Setting &setting, IShape *shape);
            void ParseWorldParameters();
            void ParseSpheres();
            void ParseCylinders();
            void ParseCones();
            void ParseTriangles();
            void ParsePlanes();
            void ParseShapes();
            void ParseMaterials();
            void ParseTransformations();
            void SetupScene();

            void setBuilder(Builder *builder) { this->builder = builder; }
            void BuildWorld();

        protected:
        private:
            Builder *builder;
            std::string _filename;
            int _width;
            int _height;
            int _bounces;
            int _iterations;
            int _frames;
            bool _display;
            Color _skybox;
            ShapeFactory _shapeFact;
            MaterialFactory _matFact;
            std::vector<Camera *> _cams;
            std::vector<IShape *> _shapes;
            IMaterial *_defaultMat;
            std::map<std::string, IMaterial *> _materials;
            libconfig::Config _cfg;
    };
}
