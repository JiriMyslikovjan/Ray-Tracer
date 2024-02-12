#include <iostream>
#include <cmath>
#include "ray_tracing/color.h"

Color::Color()
{
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Color::Color(double _r, double _g, double _b)
{
    r = _r;
    g = _g;
    b = _b;
}

Color& Color::operator+=(const Color &col)
{
    r += col.r;
    g += col.g;
    b += col.b;

    return * this;
}

Color& Color::operator*=(double n)
{
    r *= n;
    g *= n;
    b *= n;

    return * this;
}

Color& Color::operator/=(double n)
{
    r /= n;
    g /= n;
    b /= n;

    return * this;
}

Color Color::random()
{
    return Color(random_double(), random_double(), random_double());
}

Color Color::random(double min, double max)
{
    return Color(random_double(min, max), random_double(min, max), random_double(min, max));
}

void write_color(std::ostream &out, Color pixel_color, int spp)
{
    auto r = pixel_color.r;
    auto g = pixel_color.g;
    auto b = pixel_color.b;

    auto scale = 1.0 / spp;

    r *= scale;
    g *= scale;
    b *= scale;

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const Interval intensity(0.0, 1.0);

    out << static_cast<int>(255.0 * intensity.clamp(r)) << " "
        << static_cast<int>(255.0 * intensity.clamp(g)) << " "
        << static_cast<int>(255.0 * intensity.clamp(b)) << "\n";
}