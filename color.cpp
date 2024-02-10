#include "color.h"

Color::Color() : values{0} { return; }

Color::Color(const uint32_t r, const uint32_t g, const uint32_t b) 
{
    values[0] = r;
    values[1] = g;
    values[2] = b;
    return;
}

Color::Color(uint32_t values[3])
{
    for(int i = 0; i < 3; ++i) this->values[i] = values[i];
    return;
}

uint32_t Color::map_color(const float scalar) 
{ 
    return 
        (values[0] * scalar > 255 ? 255 << 16 : uint32_t(values[0] * scalar) << 16) | 
        (values[1] * scalar > 255 ? 255 << 8 : uint32_t(values[1] * scalar) << 8) |
        (values[2] * scalar > 255 ? 255 : uint32_t(values[2] * scalar));
    //return (uint32_t(values[0] * scalar) << 16) | (uint32_t(values[1] * scalar)  << 8) | uint32_t(values[2] * scalar); 
}

Color & Color::operator*=(const float op2)
{
    values[0] *= op2;
    values[1] *= op2;
    values[2] *= op2;
    return *this;
}
Color & Color::operator/=(const float op2)
{
    values[0] /= op2;
    values[1] /= op2;
    values[2] /= op2;
    return *this;
}