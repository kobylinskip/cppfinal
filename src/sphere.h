/*
    Name: Phillip Kobylinski
    File: sphere.h
    Date: 05/11/2022
    Assignment: Final Project
    Description: Header file for Sphere class
    License: See LICENSE.txt
*/

#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include <tuple>
#include "vec.h"

class Sphere
{
public:
    Sphere();
    Sphere(Vec3 cen, float r, Vec4 col, float refl, int sh);

    Vec3 GetCenter();
    void SetCenter(Vec3 cen);
    float GetRadius();
    float GetRadiusSquared();
    void SetRadius(float r);
    Vec4 GetColor();
    void SetColor(Vec4 col);
    float GetReflectivity();
    void SetReflectivity(float refl);
    int GetShininess();
    void SetShininess(int shine);

    std::tuple<float, float> IntersectRay(Vec3 rayOrigin, Vec3 rayDir);
private:
    Vec3 center;
    float radius;
    float radiusSquared; // Cached
    Vec4 color;
    float reflectivity;
    int shininess;
};

inline Vec3 Sphere::GetCenter()
{
    return this->center;
}

inline void Sphere::SetCenter(Vec3 cen)
{
    this->center = cen;
}

inline float Sphere::GetRadius()
{
    return this->radius;
}

inline float Sphere::GetRadiusSquared()
{
    return this->radiusSquared;
}

inline void Sphere::SetRadius(float r)
{
    this->radius = r;
    this->radiusSquared = r * r;
}

inline Vec4 Sphere::GetColor()
{
    return this->color;
}

inline void Sphere::SetColor(Vec4 col)
{
    this->color = col;
}

inline float Sphere::GetReflectivity()
{
    return this->reflectivity;
}

inline void Sphere::SetReflectivity(float refl)
{
    this->reflectivity = refl;
}

inline int Sphere::GetShininess()
{
    return this->shininess;
}

inline void Sphere::SetShininess(int shine)
{
    this->shininess = shine;
}

#endif // SPHERE_H_INCLUDED
