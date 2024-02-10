// light.h

#ifndef LIGHT_H
#define LIGHT_H
#include "vec3.h"

typedef class Light
{
    public:
        Light();
        Light(const float intensity);

        // Compute lighting for some point P with normal N
        virtual float compute_lighting(const Vec3 & P, const Vec3 & N, const Vec3 & V, const float s); 

    protected:
        float intensity; 
} AmbientLight;

class DirectionalLight : public Light
{
    public:
        DirectionalLight();
        DirectionalLight(const float intensity, const Vec3 & direction);

        float compute_lighting(const Vec3 & P, const Vec3 & N, const Vec3 & V, const float s); 

    private:
        Vec3 direction;
};

class PointLight : public Light
{
    public:
        PointLight();
        PointLight(const float intensity, const Vec3 & position);

        float compute_lighting(const Vec3 & P, const Vec3 & N, const Vec3 & V, const float s); 

    private:
        Vec3 position;
};
#endif
