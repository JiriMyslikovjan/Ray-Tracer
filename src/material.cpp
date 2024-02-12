#include "ray_tracing/material.h"

bool Lambertian::scatter(const Ray& r, const Hit_record& rec, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = rec.normal + random_unit_vector();

    if(scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction, r.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);

    return true;
}

bool Metal::scatter(const Ray& r, const Hit_record& rec, Color& attenuation, Ray& scattered) const
{
    vec3 ray_direction = r.direction();
    ray_direction.normalize();

    vec3 reflected = reflect(ray_direction, rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_unit_vector(), r.time());
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
}

bool Dielectric::scatter(const Ray& r, const Hit_record& rec, Color& attenuation, Ray& scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0/ri) : ri;

    vec3 unit_direction = unit_vector(r.direction());

    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3 direction;

    if(cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, rec.normal);
    
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);

    scattered = Ray(rec.p, direction, r.time());

    return true;
}

double Dielectric::reflectance(double cosine, double refraction_index)
{
    auto r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
    
    r0 *= r0;

    return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5.0);
}