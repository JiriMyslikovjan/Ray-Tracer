#pragma once

#include "ray_tracing/utils.h"
#include "ray_tracing/vec3.h"

class Perlin
{
    public:
        Perlin();

        ~Perlin();

        double noise(const point3& p) const;

        double turb(const point3& p, int depth = 7) const;
    
    private:
        static const int point_count = 256;
        vec3 * ranvec;
        int * perm_x;
        int * perm_y;
        int * perm_z;

        static int * perlin_generate_perm();

        static void permute(int * p, int n);

        static double perlin_interp(vec3 c[2][2][2], double y, double v, double w);
};