#pragma once

#include "ray_tracing/color.h"
#include "ray_tracing/vec3.h"
#include "ray_tracing/image.h"
#include "ray_tracing/perlin.h"

class Texture
{
    public:
        virtual ~Texture() = default;

        virtual Color value(double u, double v, const point3& p) const = 0;
};

class SolidColor : public Texture
{
    public:
        SolidColor(Color c) : color_value(c) {}

        SolidColor(double r, double g, double b) : SolidColor(Color(r, g, b)) {}

        Color value(double u, double v, const point3& p) const override;

    private:
        Color color_value;
};

class CheckerTexture : public Texture
{
    public:
        CheckerTexture(double _scale, std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd) 
        : inv_scale(1.0 / _scale), even(_even), odd(_odd) {}

        CheckerTexture(double _scale, Color c1, Color c2) 
        : inv_scale(1.0 / _scale), even(std::make_shared<SolidColor>(c1)), odd(std::make_shared<SolidColor>(c2)) {}

        Color value(double u, double v, const point3& p) const override;

    private:
        double inv_scale;
        std::shared_ptr<Texture> even, odd;
};

class ImageTexture : public Texture
{
    public:
        ImageTexture(const char * filename) : image(filename) {}

        Color value(double u, double v, const point3& p) const override;
    
    private:
        Image image;
};

class NoiseTexture : public Texture
{
    public:
        NoiseTexture() {}

        NoiseTexture(double _scale) : scale(_scale) {}

        Color value(double u, double v, const point3& p) const override;

    private:
        Perlin noise;
        double scale;
};