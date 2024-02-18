#include "ray_tracing/perlin.h"

Perlin::Perlin()
{
    ranvec = new vec3[point_count];

    for(int i = 0; i < point_count; ++i)
        ranvec[i] = unit_vector(vec3::random(-1.0, 1.0));

    perm_x = perlin_generate_perm();
    perm_y = perlin_generate_perm();
    perm_z = perlin_generate_perm();
}

Perlin::~Perlin()
{
    delete ranvec;
    delete perm_x;
    delete perm_y;
    delete perm_z;
}

double Perlin::noise(const point3& p) const
{
    double u = p.x - floor(p.x);
    double v = p.y - floor(p.y);
    double w = p.z - floor(p.z);

    int i = static_cast<int>(floor(p.x));
    int j = static_cast<int>(floor(p.y));
    int k = static_cast<int>(floor(p.z));

    vec3 c[2][2][2];

    for(int di = 0; di < 2; di++)
    {
        for(int dj = 0; dj < 2; dj++)
        {
            for(int dk = 0; dk < 2; dk++)
            {
                c[di][dj][dk] = ranvec[
                    perm_x[(i + di) & 255] ^
                    perm_y[(j + dj) & 255] ^
                    perm_z[(k + dk) & 255]];
            }
        }
    }

    return perlin_interp(c, u, v, w);
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

double Perlin::perlin_interp(vec3 c[2][2][2], double u, double v, double w)
{
    double uu = u * u * (3.0 - 2.0 * u);
    double vv = v * v * (3.0 - 2.0 * v);
    double ww = w * w * (3.0 - 2.0 * w);
    double accum = 0.0;
    
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                vec3 weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu)) *
                         (j * vv + (1 - j) * (1 - vv)) *
                         (k * ww + (1 - k) * (1 - ww)) *
                         dot(c[i][j][k], weight_v);
            }
        }
    }

    return accum;
}

double Perlin::turb(const point3& p, int depth) const
{
    double accum = 0.0;
    point3 temp_p = p;
    double weight = 1.0;

    for(int i = 0; i < depth; i++)
    {
        accum += weight * noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return fabs(accum);
}