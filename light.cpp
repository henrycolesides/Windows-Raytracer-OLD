// light.cpp

#include <cmath>
#include "light.h"

// Base class light with intensity - alias is AmbientLight
Light::Light() : intensity(0.0) { return; }
Light::Light(const float intensity) : intensity(intensity) { return; } 

// For ambient light, just return intensity
float Light::compute_lighting(const Vec3 & P, const Vec3 & N, const Vec3 & V, const float s)
{
    return intensity;
}



DirectionalLight::DirectionalLight() : direction(Vec3()) { return; }
DirectionalLight::DirectionalLight(const float intensity, const Vec3 & direction) : Light(intensity), direction(direction) { return; }


float DirectionalLight::compute_lighting(const Vec3 & P, const Vec3 & N, const Vec3 & V, const float s)
{
    float i = 0.0;
    Vec3 L = direction;
    float n_dot_l = L * N;

    // Diffuse reflection (matte)
    if(n_dot_l > 0) // Make sure we don't add negative spaces (if n_dot_l <= 0)
    {
        //i += (intensity * (n_dot_l / N.length()) * L.length());
        i += (intensity * n_dot_l / (N.length() * L.length()));
    }

    // Specular reflection(shiny)
    if(s != -1) // if surface is shiny
    {
        Vec3 R = (2.0 * N * (n_dot_l)) - L;
        float r_dot_v = R * V;
        if(r_dot_v > 0) // Make sure we don't add negative light intensity
        {
            i += (intensity * std::pow(r_dot_v/(R.length() * V.length()), s));
        }
    }
    return i;
}



PointLight::PointLight() : position(Vec3()) { return; }
PointLight::PointLight(const float intensity, const Vec3 & position) : Light(intensity), position(position) { return; }

float PointLight::compute_lighting(const Vec3 & P, const Vec3 & N, const Vec3 & V, const float s)
{
    float i = 0.0;
    Vec3 L = position - P;
    float n_dot_l = L * N;

    if(n_dot_l > 0) // Make sure we don't add negative spaces (if n_dot_l <= 0)
    {
        //i += (intensity * (n_dot_l / N.length()) * L.length());
        i += (intensity * n_dot_l / (N.length() * L.length()));
    }

    // Specular reflection(shiny)
    if(s != -1) // if surface is shiny
    {
        Vec3 R = (2.0 * N * (n_dot_l)) - L;
        float r_dot_v = R * V;
        if(r_dot_v > 0) // Make sure we don't add negative light intensity
        {
            i += (intensity * std::pow(r_dot_v/(R.length() * V.length()), s));
        }
    }   
    
    return i;
}