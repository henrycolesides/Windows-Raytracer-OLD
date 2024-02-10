// shapes.cpp

#include <cmath>
#include "shapes.h"

Sphere::Sphere() : position(Vec3()), radius(0.0), color(Color()), specularity(-1.0) { return; }
Sphere::Sphere(const Vec3 & position, const float radius, const Color & color, const float specularity) : position(position), radius(radius), color(color), specularity(specularity) { return; }

uint32_t Sphere::map_color()
{
    return color.map_color();
}

uint32_t Sphere::map_color(const float scalar)
{
    return color.map_color(scalar);
}

Vec3 Sphere::get_position()
{
    return position;
}

float Sphere::get_specularity()
{
    return specularity;
}


// Maybe unnecessary?
Color & Sphere::get_color()
{
    return color;
}

// Maybe unnecessary?
void Sphere::scale_color(const float scalar)
{
    color *= scalar;
    return;
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