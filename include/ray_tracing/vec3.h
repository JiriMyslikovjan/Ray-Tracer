#pragma once

#include <iostream>
#include "ray_tracing/utils.h"

void printHello();

class vec3
{
    public:
        double x, y, z;

        vec3();

        vec3(double _x, double _y, double _z);
        
        vec3 operator-() const;

        vec3& operator+=(const vec3 &vec);

        vec3& operator*=(double n);

        vec3& operator/=(double n);

        double operator[](int i) const;
        double& operator[](int i);

        double len_squared() const;

        double len() const;

        static vec3 random();

        static vec3 random(double min, double max);

        bool near_zero() const;

        inline vec3& vec3::normalize()
        {   
            double len  = this->len();

            x /= len;
            y /= len;
            z /= len;

            return * this;
        }   
};

using point3 = vec3;

inline vec3 operator+(const vec3 &vec1, const vec3 &vec2)
{
    return vec3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

inline vec3 operator-(const vec3 &vec1, const vec3 &vec2)
{
    return vec3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

inline vec3 operator*(const vec3 &vec1, const vec3 &vec2)
{
    return vec3(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

inline vec3 operator*(double n, const vec3 &vec)
{
    return vec3(vec.x * n, vec.y * n, vec.z * n);
}

inline vec3 operator*(const vec3 &vec, double n)
{
    return n * vec;
}

inline vec3 operator/(const vec3& vec, double n)
{
    return (1.0 / n) * vec;
}

inline double dot(const vec3 &vec1, const vec3 &vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}
inline vec3 cross(const vec3 &vec1, const vec3 &vec2)
{
    return vec3(vec1.y * vec2.z - vec1.z * vec2.y, 
                vec1.z * vec2.x - vec1.x * vec2.z, 
                vec1.x * vec2.y - vec1.y * vec2.x);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.len();
}

inline vec3 random_in_unit_sphere()
{
    while(true)
    {
        auto p = vec3::random(-1.0, 1.0);

        if(p.len() * p.len() < 1)
            return p;
    }
}

inline vec3 random_unit_vector()
{
    auto p = random_in_unit_sphere();
    p.normalize();

    return p;
}

// Check if vector is on correct hemisphere. If not invert it.
inline vec3 random_on_hemisphere(const vec3& normal)
{
    auto on_unit_hemisphere = random_unit_vector();

    if(dot(on_unit_hemisphere, normal) > 0.0)
        return on_unit_hemisphere;
    
    else
        return -on_unit_hemisphere;
}

vec3 reflect(const vec3& v, const vec3& n);

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat)
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - (r_out_perp.len_squared()))) * n;
    return r_out_perp + r_out_parallel;   
}

inline vec3 random_in_unit_disc()
{
    while(true)
    {
        auto p = vec3(random_double(-1.0, 1.0), random_double(-1.0, 1.0), 0.0);

        if(p.len_squared() < 1)
            return p;
    }
}
