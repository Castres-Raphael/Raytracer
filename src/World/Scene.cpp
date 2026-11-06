/*
** EPITECH PROJECT, 2024
** RayTracer [WSL: Ubuntu]
** File description:
** Scene
*/

#include <iostream>
#include <fstream>
#include <libconfig.h++>
#include <string>
#include "Scene.hpp"
#include "IShape.hpp"
#include "ObjectFactory.hpp"
#include "Camera.hpp"
#include "Definition.hpp"
#include "Matrix.hpp"
#include "Point3D.hpp"
#include "Rectangle3D.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    Scene::Scene(char *filename)
        : _filename(filename), _width(1000), _height(1000), _bounces(10), _iterations(10), _frames(10),
        _display(false), _skybox(Color(0, 0, 0))
    {
        std::ifstream file(_filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << _filename << std::endl;
            return;
        }
        file.close();
        try {
            _cfg.readFile(_filename.c_str());
        } catch (libconfig::FileIOException &e) {
            throw FileNotFound(_filename);
        } catch (libconfig::ParseException &e) {
            throw ParseError("Parse error at " + std::string(e.getFile()) + ":" + std::to_string(e.getLine()) + " - " + e.getError());
        }
        _defaultMat = _matFact.createFlat(Color(122, 27, 111), 1);
        SetupScene();
    }

    Scene::~Scene()
    {
        for (auto &shape : _shapes)
            delete shape;
        for (auto &cam : _cams)
            delete cam;
        for (auto &mat : _materials)
            delete mat.second;
        delete _defaultMat;
    }

    Math::Matrix Scene::GetScaleMatrix(const libconfig::Setting &setting)
    {
        return Math::Matrix({setting[0], 0, 0, 0}, {0, setting[1], 0, 0}, {0, 0, setting[2], 0}, {0, 0, 0, 1});
    }

    Math::Matrix Scene::GetTranslationMatrix(const libconfig::Setting &setting)
    {
        return Math::Matrix({1, 0, 0, setting[0]}, {0, 1, 0, setting[1]}, {0, 0, 1, setting[2]}, {0, 0, 0, 1});
    }

    Math::Matrix Scene::GetRotationMatrix(float angle, std::string axis)
    {
        Math::Matrix mat;

        if (axis == "x")
            Math::Matrix::createXRotation(angle, mat);
        else if (axis == "y")
            Math::Matrix::createYRotation(angle, mat);
        else if (axis == "z")
            Math::Matrix::createZRotation(angle, mat);
        return mat;
    }

    void Scene::ParseWorldParameters()
    {
        Math::Rectangle3D origin;
        Math::Rectangle3D screen;
        try {
            _cfg.lookupValue("World.width", _width);
            _cfg.lookupValue("World.height", _height);
            _cfg.lookupValue("World.bounces", _bounces);
            _cfg.lookupValue("World.iterations", _iterations);
            _cfg.lookupValue("World.frames", _frames);
            _cfg.lookupValue("World.skybox.r", _skybox._x);
            _cfg.lookupValue("World.skybox.g", _skybox._y);
            _cfg.lookupValue("World.skybox.b", _skybox._z);
            _cfg.lookupValue("World.display", _display);
            const libconfig::Setting &cameras = _cfg.lookup("World.cameras");
            for (int i = 0; i < cameras.getLength(); ++i) {
                origin._origin = GetPoint3D(cameras[i]["origin"]["origin"]);
                origin._bottom_side = GetVector3D(cameras[i]["origin"]["botSide"]);
                origin._left_side = GetVector3D(cameras[i]["origin"]["leftSide"]);
                screen._origin = GetPoint3D(cameras[i]["screen"]["origin"]);
                screen._bottom_side = GetVector3D(cameras[i]["screen"]["botSide"]);
                screen._left_side = GetVector3D(cameras[i]["screen"]["leftSide"]);
                bool antiAliasing = cameras[i]["anti_aliasing"];
                bool depthField = cameras[i]["depth_of_field"];
                Camera *tmp = new Camera(origin, screen, antiAliasing, depthField);
                _cams.push_back(tmp);
            }
        } catch (libconfig::SettingTypeException &e) {
            throw TypeError(e.getPath());
        } catch (libconfig::SettingNotFoundException &e) {
            throw ParseError(e.getPath());
        }
    }

    void Scene::ParseMaterials()
    {
        try {
            if (_cfg.exists("Materials.flats")) {
                const libconfig::Setting &flats = _cfg.lookup("Materials.flats");
                for (int i = 0; i < flats.getLength(); ++i) {
                    _materials[flats[i]["name"]] = _matFact.createFlat(Color(flats[i]["color"][0], flats[i]["color"][1], flats[i]["color"][2]),
                        flats[i]["intensity"]);
                }
            }
            if (_cfg.exists("Materials.reflectors")) {
                const libconfig::Setting &reflects = _cfg.lookup("Materials.reflectors");
                for (int i = 0; i < reflects.getLength(); ++i) {
                    _materials[reflects[i]["name"]] = _matFact.createMirror(Color(reflects[i]["color"][0], reflects[i]["color"][1], reflects[i]["color"][2]));
                }
            }
        } catch (libconfig::SettingTypeException &e) {
            throw TypeError(e.getPath());
        } catch (libconfig::SettingNotFoundException &e) {
            throw ParseError(e.getPath());
        }
    }

    void Scene::ApplyShapeOptions(const libconfig::Setting &setting, IShape *shape)
    {
        Math::Matrix mat;

        if (setting.exists("scale")) {
            mat = GetScaleMatrix(setting["scale"]);
            shape->scale(mat);
        }
        if (setting.exists("translation")) {
            mat = GetTranslationMatrix(setting["translation"]);
            shape->translation(mat);
        }
        if (setting.exists("rotation")) {
            mat = GetRotationMatrix(setting["rotation"]["angle"], (setting["rotation"]["axis"]));
            shape->rotation(mat);
        }
        if (setting.exists("material")) {
            if (_materials.find(setting["material"]) == _materials.end()) {
                std::cerr << "Error: Material " << std::string(setting["material"]) << " not found, applying default" << std::endl;
                shape->setMaterial(_defaultMat);
            }
            else {
                shape->setMaterial(_materials[setting["material"]]);
            }
        } else {
            shape->setMaterial(_defaultMat);
        }
    }

    void Scene::ParseSpheres()
    {
        if (!_cfg.exists("Shapes.spheres"))
            return;
        const libconfig::Setting &spheres = _cfg.lookup("Shapes.spheres");
        for (int i = 0; i < spheres.getLength(); ++i) {
            IShape *sphere = _shapeFact.createSphere(GetPoint3D(spheres[i]["origin"]), spheres[i]["radius"]);
            ApplyShapeOptions(spheres[i], sphere);
            _shapes.push_back(sphere);
        }
    }

    void Scene::ParseCylinders()
    {
        if (!_cfg.exists("Shapes.cylinders"))
            return;
        const libconfig::Setting &cylinders = _cfg.lookup("Shapes.cylinders");
        for (int i = 0; i < cylinders.getLength(); ++i) {
            IShape *cylinder = _shapeFact.createCylinder(
                GetPoint3D(cylinders[i]["origin"]), cylinders[i]["radius"],
                GetVector3D(cylinders[i]["direction"]));
            ApplyShapeOptions(cylinders[i], cylinder);
            _shapes.push_back(cylinder);
        }
    }

    void Scene::ParseCones()
    {
        if (!_cfg.exists("Shapes.cones"))
            return;
        const libconfig::Setting &cones = _cfg.lookup("Shapes.cones");
        for (int i = 0; i < cones.getLength(); ++i) {
            IShape *cone = _shapeFact.createCone(GetPoint3D(cones[i]["origin"]), cones[i]["angle"],
                GetVector3D(cones[i]["direction"]));
            ApplyShapeOptions(cones[i], cone);
            _shapes.push_back(cone);
        }
    }

    void Scene::ParseTriangles()
    {
        if (!_cfg.exists("Shapes.triangles"))
            return;
        const libconfig::Setting &triangles = _cfg.lookup("Shapes.triangles");
        for (int i = 0; i < triangles.getLength(); ++i) {
            IShape *triangle = _shapeFact.createTriangle(GetPoint3D(triangles[i]["p1"]),
                GetPoint3D(triangles[i]["p2"]), GetPoint3D(triangles[i]["p3"]));
            ApplyShapeOptions(triangles[i], triangle);
            _shapes.push_back(triangle);
        }
    }

    void Scene::ParsePlanes()
    {
        if (!_cfg.exists("Shapes.planes"))
            return;
        const libconfig::Setting &planes = _cfg.lookup("Shapes.planes");
        for (int i = 0; i < planes.getLength(); ++i) {
            IShape *plane = _shapeFact.createPlane(GetPoint3D(planes[i]["origin"]),
                GetVector3D(planes[i]["normal"]));
            ApplyShapeOptions(planes[i], plane);
            _shapes.push_back(plane);
        }
    }

    void Scene::ParseShapes()
    {
        try {
            ParseSpheres();
            ParseCylinders();
            ParseCones();
            ParseTriangles();
            ParsePlanes();
        } catch (libconfig::SettingTypeException &e) {
            throw TypeError(e.getPath());
        } catch (libconfig::SettingNotFoundException &e) {
            throw ParseError(e.getPath());
        }
    }

    void Scene::SetupScene()
    {
        ParseWorldParameters();
        ParseMaterials();
        ParseShapes();
    }

    void Scene::BuildWorld()
    {
        builder->setResolution(_width, _height);
        builder->setWorldParameters(_bounces, _iterations, _skybox, _frames, _display);
        builder->setCameras(_cams);
        builder->setShapes(_shapes);
    }
}
