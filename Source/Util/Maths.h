#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
constexpr float PI = 3.14159265f;
constexpr float MIN_PI = 3.14f;

template <typename T>
T toRadians(T degrees)
{
    return degrees * PI / 180;
}

template <typename T>
T toDegrees(T radians)
{
    return (radians * 180) / PI;
}

template <typename T>
float EuclideanDistance(T a,T b)
{
    return hypot(a.x-b.x,a.y-b.y);
}