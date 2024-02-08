// shapes.cpp

#include <cmath>
#include "shapes.h"

Sphere::Sphere() : position(Vec3()), radius(0.0), color(Color()) { return; }
Sphere::Sphere(const Vec3 & position, const float radius, const Color & color) : position(position), radius(radius), color(color) { return; }

uint32_t Sphere::map_color()
{
    return color.map_color();
}

Vec3 Sphere::intersect_ray(Vec3 O, Vec3 D)
{
    Vec3 CO = O - position;

    float a = D * D;
    float b = 2 * (CO * D);
    float c = (CO * CO) - (radius * radius);

    float discriminant = (b * b) - (4 * a * c);
    if(discriminant < 0.0)
    {
        return Vec3(__FLT_MAX__, __FLT_MAX__, 0);
    }

    float t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    float t2 = (-b - std::sqrt(discriminant)) / (2 * a);
    return Vec3(t1, t2, 0.0);
}