#pragma once

#include "ray_tracing/utils.h"
#include "ray_tracing/vec3.h"
#include "ray_tracing/ray.h"

class Aabb
{
    public:
        Interval x, y, z;

        Aabb();

        Aabb(const Interval& _x, const Interval& _y, const Interval& _z) : x(_x), y(_y), z(_z) {}

        Aabb(const point3& a, const point3& b);
        
        Aabb(const Aabb& a, const Aabb& b);

        const Interval& axis(int n) const;

        bool hit(const Ray& r, Interval ray_t) const;
};