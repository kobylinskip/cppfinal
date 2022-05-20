/*
    Name: Phillip Kobylinski
    File: vec.h
    Date: 05/11/2022
    Assignment: Final Project
    Description: Header file for mathematical vectors
    License: See LICENSE.txt
*/

#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

inline float Clamp(float a, float lower, float upper)
{
    return std::min(std::max(a, lower), upper);
}

inline float Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

inline float Radians(float deg)
{
    return float((deg/180.0f) * M_PI);
}

struct Vec3
{
    float x, y, z;
    Vec3()
        : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(float x, float y, float z)
        : x(x), y(y), z(z) {}
};

inline Vec3 operator-(Vec3 a)
{
    return Vec3(-a.x, -a.y, -a.z);
}

inline Vec3 operator*(Vec3 a, float b)
{
    return Vec3(a.x * b, a.y * b, a.z * b);
}

inline Vec3 operator*(float a, Vec3 b)
{
    return b * a;
}

inline Vec3 operator+(Vec3 a, Vec3 b)
{
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(Vec3 a, Vec3 b)
{
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline float Dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Length(Vec3 a)
{
    return sqrtf(Dot(a, a));
}

inline Vec3 Normalize(Vec3 a)
{
    float l = Length(a);
    return Vec3(a.x/l, a.y/l, a.z/l);
}

inline Vec3 Reflect(Vec3 a, Vec3 normal)
{
    return (2.0f * normal * Dot(normal, a)) - a;
}

struct Vec4
{
    float x, y, z, w;
    Vec4()
        : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vec4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w) {}
};

inline Vec4 operator*(Vec4 a, float b)
{
    return Vec4(a.x * b, a.y * b, a.z * b, a.w * b);
}

inline Vec4 operator*(float a, Vec4 b)
{
    return b * a;
}

inline Vec4 Mix(Vec4 a, Vec4 b, float t)
{
    return Vec4(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t),
                Lerp(a.z, b.z, t), Lerp(a.w, b.w, t));
}

#endif // VEC_H_INCLUDED
