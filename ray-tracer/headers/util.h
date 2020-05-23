// A generic header file containing some useful and common, constants and functions.
#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Util functions
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180;
}

// Common headers
#include "../headers/vec3.h"
#include "../headers/ray.h"