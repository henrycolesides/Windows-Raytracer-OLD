// color.h

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

class Color
{
    public:
        Color();
        Color(uint32_t r, uint32_t g, uint32_t b);
        Color(uint32_t values[3]);
        inline uint32_t map_color() { return (values[0] << 16) | (values[1] << 8) | (values[2]); }
        uint32_t map_color(const float scalar);
        //{ return (uint32_t(values[0] * scalar) << 16) | (uint32_t(values[1] * scalar)  << 8) | uint32_t(values[2] * scalar); }
        static inline uint32_t map_color(uint32_t r, uint32_t g, uint32_t b) { return (r << 16) | (g << 8) | (b); }

        Color & operator*=(const float op2);
        Color & operator/=(const float op2);
    private:
        uint32_t values[3];
};

#endif