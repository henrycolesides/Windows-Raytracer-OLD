// shapes.h

#ifndef SHAPES_H
#define SHAPES_H

#include <stdint.h>
#include "vec3.h"
#include "color.h"

class Sphere
{
    public:
        Sphere();
        Sphere(const Vec3 & position, const float radius, const Color & color);
        Vec3 intersect_ray(Vec3 O, Vec3 D);
        uint32_t map_color();

    private:
        Vec3 position; 
        float radius;        
        Color color;
};

#endif