/*
    Name: Phillip Kobylinski
    File: point_light.h
    Date: 05/11/2022
    Assignment: Final Project
    Description: Header file for PointLight class
    License: See LICENSE.txt
*/

#ifndef POINT_LIGHT_H_INCLUDED
#define POINT_LIGHT_H_INCLUDED

#include "vec.h"

class PointLight
{
public:
    PointLight();
    PointLight(Vec3 p, float i);

    Vec3 GetPos();
    void SetPos(Vec3 p);
    float GetIntensity();
    void SetIntensity(float i);
private:
    Vec3 pos;
    float intensity;
};

inline Vec3 PointLight::GetPos()
{
    return this->pos;
}

inline void PointLight::SetPos(Vec3 p)
{
    this->pos = p;
}

inline float PointLight::GetIntensity()
{
    return this->intensity;
}

inline void PointLight::SetIntensity(float i)
{
    this->intensity = i;
}

#endif // POINT_LIGHT_H_INCLUDED
