#include "ray_tracing/aabb.h"

Aabb::Aabb()
{}

Aabb::Aabb(const point3& a, const point3& b)
{
    x = Interval(std::fmin(a.x, b.x), std::fmax(a.x, b.x));
    y = Interval(std::fmin(a.y, b.y), std::fmax(a.y, b.y));
    z = Interval(std::fmin(a.z, b.z), std::fmax(a.z, b.z));
}

Aabb::Aabb(const Aabb& box0, const Aabb& box1)
{
    x = Interval(box0.x, box1.x);
    y = Interval(box0.y, box1.y);
    z = Interval(box0.z, box1.z);
}

const Interval& Aabb::axis(int n) const
{
    if(n == 2)
        return z;
    
    if(n == 1)
        return y;

    return x;
}

bool Aabb::hit(const Ray& r, Interval ray_t) const
{
    for(int a = 0; a < 3; a++)
    {
        auto invD = 1.0 / r.direction()[a];
        auto orig = r.origin()[a];

        auto t0 = (axis(a).min - orig) * invD;
        auto t1 = (axis(a).max - orig) * invD;

        if(invD < 0.0)
            std::swap(t0, t1);
        
        if(t0 > ray_t.min)
            ray_t.min = t0;
        
        if(t1 < ray_t.max)
            ray_t.max = t1;
        
        if(ray_t.max <= ray_t.min)
            return false;
    }

    return true;
}