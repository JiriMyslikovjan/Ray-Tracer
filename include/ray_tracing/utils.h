#pragma once

#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utilitz functions

inline double degrees_to_radians(double degrees) 
{
    return degrees * pi / 180.0;
}

// Returns random double from interval <0,1)
inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

inline int random_int(int min, int max)
{
    return static_cast<int>(random_double(min, max));
}

class Interval
{
    public:
        double min, max;

        Interval() : min(-infinity), max(infinity) {}

        Interval(double _min, double _max);

        Interval(const Interval& a, const Interval& b) : min(fmin(a.min, b.min)), max(fmax(a.max, b.max)) {}

        bool contains(double x) const;
        
        bool surrounds(double x) const;

        double clamp(double x) const;

        double size() const;

        Interval expand(double delta) const;

        static const Interval empty, universe;
};

const static Interval empty(infinity, -infinity);
const static Interval universe(-infinity, infinity);