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
        static inline uint32_t map_color(uint32_t r, uint32_t g, uint32_t b) { return (r << 16) | (g << 8) | (b); }

    private:
        uint32_t values[3];
};

#endif