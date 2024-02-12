#include "ray_tracing/ray.h"

Ray::Ray()
{}

point3 Ray::origin() const { return orig; }

vec3 Ray::direction() const { return dir; }

double Ray::time() const { return tm;} 

point3 Ray::at(double n) const
{
    return orig + n * dir;
}
