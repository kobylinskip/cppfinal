/*
    Name: Phillip Kobylinski
    File: scene.cpp
    Date: 05/11/2022
    Assignment: Final Project
    Description: Implementation file for Scene class
    License: See LICENSE.txt
*/

#include "scene.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

//
// Function:    Vec4ToUint32
// Parameters:  Vec4 color
// Returns:     uint32_t color
// Description: Convert a Vec4 color to a uint32_t color
//
static uint32_t Vec4ToUint32(Vec4 color)
{
    uint32_t result = uint32_t(uint8_t(color.x * 255.0f)) << 24
                    | uint32_t(uint8_t(color.y * 255.0f)) << 16
                    | uint32_t(uint8_t(color.z * 255.0f)) << 8
                    | uint32_t(uint8_t(color.w * 255.0f));
    return result;
}

//
// Function:    Scene::LoadFromFile
// Parameters:  Input file
// Returns:     Boolean flag indicating whether parsing was successful
// Description: Parses a scene file and loads data into Scene object
//
bool Scene::LoadFromFile(std::ifstream &file)
{
    //
    //  Scene file reference:
    //
    //  background color
    //  camera       pos_x pos_y pos_z yaw pitch roll
    //  sphere       pos_x pos_y pos_z radius r g b reflect shine
    //  ambientLight intensity
    //  pointLight   pos_x pos_y pos_z r g b intensity
    //
    int line = 1;
    while (!file.eof()) {
        string command;
        file >> std::ws;
        getline(file, command, ' ');
        if (!command.empty()) {
            if (command == "background") {
                float r, g, b;
                file >> r >> g >> b;
                this->bgColor = Vec4(r, g, b, 1.0f);
            } else if (command == "camera") {
                float x, y, z, yaw, pitch, roll;
                file >> x >> y >> z >> yaw >> pitch >> roll;
                this->camPos = Vec3(x, y, z);
                this->camYaw = yaw;
                this->camPitch = pitch;
                this->camRoll = roll;
            } else if (command == "sphere") {
                float radius, x, y, z, r, g, b;
                float refl;
                int shine;
                file >> x >> y >> z >> radius >> r >> g >> b >> refl >> shine;
                this->spheres.emplace_back(Vec3(x, y, z), radius, Vec4(r, g, b, 1.0f), refl, shine);
            } else if (command == "ambientLight") {
                float intensity;
                file >> intensity;
                this->ambientLightIntensity += intensity;
            } else if (command == "pointLight") {
                float x, y, z, intensity;
                file >> x >> y >> z >> intensity;
                this->pointLights.emplace_back(Vec3(x, y, z), intensity);
            } else {
                cout << "Error: Line " << line << " unknown command " << command << endl;
                return false; // Unknown command
            }
            if (file.fail()) {
                cout << "Error: line " << line << endl;
                return false; // Bad input
            }
        }
        ++line;
    }
    return true;
}

//
// Function:    Scene::Render
// Parameters:  Pixel buffer, width, height
// Returns:     None
// Description: Render the scene to the pixel buffer
//
void Scene::Render(uint32_t *pixels, int w, int h)
{
    float yaw = Radians(this->camYaw);
    float pitch = Radians(this->camPitch);
    float roll = Radians(this->camRoll);
    for (int y = -h/2; y < h/2; ++y) {
        for (int x = -w/2; x < w/2; ++x) {
            Vec3 rayDir(float(x)/float(w), float(y)/float(h), 1.0f);
            // Rotate rayDir
            rayDir = rayDir.x * Vec3( cosf(roll), sinf(roll), 0.0f)
                   + rayDir.y * Vec3(-sinf(roll), cosf(roll), 0.0f)
                   + rayDir.z * Vec3(0.0f, 0.0f, 1.0f);
            rayDir = rayDir.x * Vec3(1.0f, 0.0f, 0.0f)
                   + rayDir.y * Vec3(0.0f,  cosf(pitch), sinf(pitch))
                   + rayDir.z * Vec3(0.0f, -sinf(pitch), cosf(pitch));
            rayDir = rayDir.x * Vec3(cosf(yaw), 0.0f, -sinf(yaw))
                   + rayDir.y * Vec3(0.0f, 1.0f, 0.0f)
                   + rayDir.z * Vec3(sinf(yaw), 0.0f,  cosf(yaw));
            Vec4 color = this->TraceRay(this->camPos, rayDir, 1.0f, numeric_limits<float>::infinity());
            uint32_t pixel = Vec4ToUint32(color);
            int xPx = x + (w/2);
            int yPx = h - (y + (h/2)) - 1;
            pixels[(yPx * w) + xPx] = pixel;
        }

    }
}

//
// Function:    Scene::TraceRay
// Parameters:  Ray, max and min t, recursion limit
// Returns:     Result color
// Description: Trace a light ray's path and find the resulting color
//
Vec4 Scene::TraceRay(Vec3 rayOrigin, Vec3 rayDir, float tMin, float tMax, unsigned recurLimit)
{
    Sphere *sphere;
    Vec3 intersect;
    std::tie(sphere, intersect) = this->NearestSphere(rayOrigin, rayDir, tMin, tMax);
    if (sphere) {
        Vec3 normal = Normalize(intersect - sphere->GetCenter());
        float intensity = this->ComputeLighting(sphere, intersect, normal);
        Vec4 color = sphere->GetColor() * Clamp(intensity, 0.0f, 1.0f);
        if (sphere->GetReflectivity() > 0.0f && recurLimit > 0) {
            Vec4 reflection = this->TraceRay(intersect, Normalize(Reflect(-rayDir, normal)),
                    0.1f, numeric_limits<float>::infinity(), recurLimit - 1);
            color = Mix(color, reflection, sphere->GetReflectivity());
            return color;
        }
    }
    return this->bgColor;
}

//
// Function:    Scene::ComputeLighting
// Parameters:  Sphere, position, normal vector
// Returns:     Light intensity
// Description: Compute lighting for a position on a sphere
//
float Scene::ComputeLighting(Sphere *sphere, Vec3 position, Vec3 normal)
{
    int shininess = sphere->GetShininess();
    float intensity = this->ambientLightIntensity;
    for (auto &l : this->pointLights) {
        Vec3 pl = l.GetPos() - position; // position to light
        float dist = Length(pl);
        // Check if there is path from the light source to this point of the sphere
        Sphere *occludingSphere;
        Vec3 dummy;
        std::tie(occludingSphere, dummy) = this->NearestSphere(position, Normalize(pl), 0.01f, dist);
        if (!occludingSphere) {
            // Diffuse
            float nl = Dot(normal, pl);
            if (nl > 0.0f) {
                intensity += l.GetIntensity() * (nl/dist);
            }
            // Specular
            Vec3 pc = this->camPos - position;
            if (shininess >= 0) {
                Vec3 reflDir = (2.0f * normal * Dot(normal, pl)) - pl;
                float c = Dot(reflDir, pc);
                if (c > 0.0f) {
                    intensity += l.GetIntensity() * powf(c/(Length(reflDir) * Length(pc)), float(shininess));
                }
            }
        }
    }
    return intensity;
}

//
// Function:    Scene::NearestSphere
// Parameters:  Ray
// Returns:     Nearest sphere or null, intersecting position
// Description: Find the nearest sphere that hits a ray
//
std::tuple<Sphere *, Vec3> Scene::NearestSphere(Vec3 rayOrigin, Vec3 rayDir, float tMin, float tMax)
{
    float tClosest = numeric_limits<float>::infinity();
    Sphere *sphere = nullptr;
    for (auto &s : this->spheres) {
        float t1, t2;
        std::tie(t1, t2) = s.IntersectRay(rayOrigin, rayDir);
        if (tMin <= t1 && t1 <= tMax && t1 < tClosest) {
            tClosest = t1;
            sphere = &s;
        }
        if (tMin <= t2 && t2 <= tMax && t2 < tClosest) {
            tClosest = t2;
            sphere = &s;
        }
    }
    return {sphere, sphere ? rayOrigin + (tClosest * rayDir) : Vec3()};
}
