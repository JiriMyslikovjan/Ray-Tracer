#include "ray_tracing/texture.h"

Color SolidColor::value(double u, double v, const point3& p) const 
{
    return color_value;
}

Color CheckerTexture::value(double u, double v, const point3& p) const 
{
    auto x_integer = static_cast<int>(std::floor(inv_scale * p.x));
    auto y_integer = static_cast<int>(std::floor(inv_scale * p.y));
    auto z_integer = static_cast<int>(std::floor(inv_scale * p.z));

    bool is_even = (x_integer + y_integer + z_integer) % 2 == 0;

    if(is_even)
        return even->value(u, v, p);
    
    return odd->value(u, v, p);
}

Color ImageTexture::value(double u, double v, const point3& p) const 
{
    if(image.height() <= 0)
        return Color(1.0, 0.0, 1.0);

    u = Interval(0.0, 1.0).clamp(u);
    v = 1.0 - Interval(0.0, 1.0).clamp(v);

    auto i = static_cast<int>(u * image.width());
    auto j = static_cast<int>(v * image.height());

    auto pixel = image.pixel_data(i, j);

    auto color_scale = 1.0 / 255.0;

    return Color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}