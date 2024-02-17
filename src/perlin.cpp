#include "ray_tracing/perlin.h"

Perlin::Perlin()
{
    ranfloat = new double[point_count];

    for(int i = 0; i < point_count; ++i)
        ranfloat[i] = random_double();

    perm_x = perlin_generate_perm();
    perm_y = perlin_generate_perm();
    perm_z = perlin_generate_perm();
}

Perlin::~Perlin()
{
    delete ranfloat;
    delete perm_x;
    delete perm_y;
    delete perm_z;
}

double Perlin::noise(const point3& p) const
{
    auto i = static_cast<int>(4.0 * p.x) & 255;
    auto j = static_cast<int>(4.0 * p.y) & 255;
    auto k = static_cast<int>(4.0 * p.z) & 255;

    return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
}

int * Perlin::perlin_generate_perm()
{
    auto p = new int[point_count];

    for(int i = 0; i < point_count; i++)
        p[i] = i;
    
    permute(p, point_count);

    return p;
}

void Perlin::permute(int * p, int n)
{
    for(int i = n - 1; i > 0; i--)
    {
        int target = random_int(0, i);
        int tmp = p[i];

        p[i] = p[target];
        p[target] = tmp;
    }
}