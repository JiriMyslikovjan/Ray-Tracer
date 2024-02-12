#include "ray_tracing/vec3.h"

void printHello()
{
    std::cout << "Hello world\n";
}



vec3::vec3()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

vec3::vec3(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}
vec3 vec3::operator-() const
{
    return vec3(-x, -y, -z);
}

vec3& vec3::operator+=(const vec3 &vec)
{
            x += vec.x;
            y += vec.y;
            z += vec.z;

            return * this;
}

vec3& vec3::operator*=(double n)
        {
            x *= n;
            y *= n;
            z *= n;

            return * this;
        }

vec3& vec3::operator/=(double n)
{
    x /= n;
    y /= n;
    z /= n;

    return * this;
}

double vec3::operator[](int i) const 
{ 
    switch(i)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return x;
    }
}

double& vec3::operator[](int i)
{ 
    switch(i)
    {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return x;
    }
}

double vec3::len_squared() const
{
    return x * x + y * y + z * z;
}

double vec3::len() const
{
    return std::sqrt(len_squared());
}

vec3 vec3::random()
{
    return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(double min, double max)
{
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

bool vec3::near_zero() const
{
    auto s = 1e-8;
    return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v, n) * n;
}


void printVector(const vec3 &vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")\n";
}