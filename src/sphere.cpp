/*
    Name: Phillip Kobylinski
    File: sphere.cpp
    Date: 05/11/2022
    Assignment: Final Project
    Description: Implementation file for Sphere class
    License: See LICENSE.txt
*/

#include "sphere.h"

#include <cmath>
#include <limits>

using namespace std;

Sphere::Sphere()
    : radius(0.0f), radiusSquared(0.0f), reflectivity(0.0f), shininess(0)
{
}

Sphere::Sphere(Vec3 cen, float r, Vec4 col, float refl, int sh)
    : center(cen), color(col), radius(r), radiusSquared(r * r), reflectivity(refl), shininess(sh)
{
}

//
// Function:    Sphere::IntersectRay
// Parameters:  Ray origin, ray direction
// Returns:     Returns t1 and t2 where ray intersects sphere
// Description: Find the point of intersection between a sphere and ray
//
std::tuple<float, float> Sphere::IntersectRay(Vec3 rayOrigin, Vec3 rayDir)
{
    float t1 = numeric_limits<float>::infinity();
    float t2 = t1;
    Vec3 oc = rayOrigin - this->center;
    float k1 = Dot(rayDir, rayDir);
    float k2 = 2.0f * Dot(oc, rayDir);
    float k3 = Dot(oc, oc) - this->radiusSquared;
    float discr = (k2 * k2) - (4.0f * k1 * k3);
    if (discr >= 0.0f) {
        float discrRoot = sqrtf(discr);
        t1 = (-k2 + discrRoot)/(2.0f * k1);
        t2 = (-k2 - discrRoot)/(2.0f * k1);
    }
    return {t1, t2};
}
