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