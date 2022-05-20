/*
    Name: Phillip Kobylinski
    File: point_light.cpp
    Date: 05/11/2022
    Assignment: Final Project
    Description: Implementation file for PointLight class
    License: See LICENSE.txt
*/

#include "point_light.h"

PointLight::PointLight()
{
}

PointLight::PointLight(Vec3 p, float i)
    : pos(p), intensity(i)
{
}
