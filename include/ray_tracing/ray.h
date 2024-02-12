#pragma once
#include "ray_tracing/vec3.h"

class Ray
{
    public:
        Ray();

        Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) , tm(0.0) {}

        Ray(const point3& origin, const vec3& direction, double time = 0.0) : orig(origin), dir(direction) , tm(time) {}
        
        point3 origin() const;

        vec3 direction() const;

        double time() const;

        point3 at(double n) const;

    private:
        point3 orig;
        vec3 dir;
        double tm;
};