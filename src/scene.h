/*
    Name: Phillip Kobylinski
    File: scene.h
    Date: 05/11/2022
    Assignment: Final Project
    Description: Header file for Scene class
    License: See LICENSE.txt
*/

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <cstdint>
#include <fstream>
#include <vector>
#include <memory>
#include "sphere.h"
#include "point_light.h"

class Scene
{
public:
    bool LoadFromFile(std::ifstream &file);
    void Render(std::vector<std::unique_ptr<uint32_t>> &buffers, int w, int h);
private:
    std::vector<std::tuple<Vec3, float, float, float>> cameras;
    Vec4 bgColor;
    float ambientLightIntensity = 0.0f;
    std::vector<Sphere> spheres;
    std::vector<PointLight> pointLights;

    Vec4 TraceRay(Vec3 rayOrigin, Vec3 rayDir, float tMin, float tMax, unsigned recurLimit = 3);
    float ComputeLighting(Vec3 camPos, Sphere *sphere, Vec3 position, Vec3 normal);
    std::tuple<Sphere *, Vec3> NearestSphere(Vec3 rayOrigin, Vec3 rayDir, float tMin, float tMax);
};

#endif // SCENE_H_INCLUDED
