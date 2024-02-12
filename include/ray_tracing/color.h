#pragma once
#include <iostream>
#include <cmath>
#include "ray_tracing/utils.h"

class Color
{
    public:
        double r, g, b;

        Color();

        Color(double _r, double _g, double _b);

        Color& operator+=(const Color &col);

        Color& operator*=(double t);

        Color& operator/=(double n);

        static Color random();

        static Color random(double min, double max);
};

inline double linear_to_gamma(double linear_component)
{
    return std::sqrt(linear_component);
}

void write_color(std::ostream &out, Color pixel_color, int spp);

inline Color operator+(const Color &col1, const Color &col2)
{
    return Color(col1.r + col2.r, col1.g + col2.g, col1.b + col2.b);
}

inline Color operator-(const Color &col1, const Color &col2)
{
    return Color(col1.r - col2.r, col1.g - col2.g, col1.b - col2.b);
}

inline Color operator*(const Color &col1, const Color &col2)
{
    return Color(col1.r * col2.r, col1.g * col2.g, col1.b * col2.b);
}

inline Color operator*(double n, const Color &col)
{
    return Color(col.r * n, col.g * n, col.b * n);
}

inline Color operator*(const Color &col, double n)
{
    return n * col;
}

inline Color operator/(const Color &col1, const Color &col2)
{
    return Color(col1.r / col2.r, col1.g / col2.g, col1.b / col2.b);
}
