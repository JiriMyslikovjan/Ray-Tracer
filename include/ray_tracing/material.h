#pragma once

#include "ray_tracing/vec3.h"
#include "ray_tracing/color.h"
#include "ray_tracing/ray.h"
#include "ray_tracing/object.h"
#include "ray_tracing/texture.h"

class Material 
{
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray& r, const Hit_record& rec, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
    public:
        Lambertian(const Color& a) : albedo(std::make_shared<SolidColor>(a)) {}

        Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}

        bool scatter(const Ray& r, const Hit_record& rec, Color& attenuation, Ray& scattered) const override;
    
    private:
        std::shared_ptr<Texture> albedo;

};

class Metal : public Material
{
    public:
        Metal(const Color& a, double fuzziness) : albedo(a), fuzz(fuzziness) {}

        bool scatter(const Ray& r, const Hit_record& rec, Color& attenuation, Ray& scattered) const override;

    private:
        Color albedo;
        double fuzz;
};

class Dielectric : public Material
{
    public:
        Dielectric(double index_of_refraction) : ri(index_of_refraction) {}

        bool scatter(const Ray& r, const Hit_record& rec, Color& attenuation, Ray& scattered) const override;

    private:
        double ri;

        static double reflectance(double cosine, double refraction_index);
};