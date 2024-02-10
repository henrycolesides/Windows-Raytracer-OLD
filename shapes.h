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
        Sphere(const Vec3 & position, const float radius, const Color & color, float specularity);
        Vec3 intersect_ray(Vec3 O, Vec3 D);
        uint32_t map_color();
        uint32_t map_color(const float scalar);
        Vec3 get_position();
        float get_specularity();
        // Maybe unnecesary? 
        Color & get_color();
        void scale_color(const float scalar);

    private:
        Vec3 position; 
        float radius;        
        Color color;
        float specularity;  // Specular constant
                            // Exponent of cos(angle between v and r)
};

#endif