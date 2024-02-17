#pragma once

#include "ray_tracing/utils.h"
#include "ray_tracing/vec3.h"

class Perlin
{
    public:
        Perlin();

        ~Perlin();

        double noise(const point3& p) const;
    
    private:
        static const int point_count = 256;
        double * ranfloat;
        int * perm_x;
        int * perm_y;
        int * perm_z;

        static int * perlin_generate_perm();

        static void permute(int * p, int n);
};