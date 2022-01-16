#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

#include "ray.hpp"
#include "vecmath.h"

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max+1));
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline static Vector3f randomV() {
        return Vector3f(random_double(), random_double(), random_double());
    }

inline static Vector3f randomV(double min, double max) {
        return Vector3f(random_double(min,max), random_double(min,max), random_double(min,max));
    }

Vector3f random_in_unit_sphere() {
    while (true) {
        auto p = randomV(-1,1);
        if (p.squaredLength() >= 1) 
            continue;
        return p;
    }
}

Vector3f random_unit_vector() {
    return random_in_unit_sphere().normalized();
}

Vector3f random_in_hemisphere(const Vector3f& normal) {
    Vector3f in_unit_sphere = random_in_unit_sphere();
    if (Vector3f::dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

Vector3f reflect(const Vector3f& v, const Vector3f& n) {
    return v - 2 * Vector3f::dot(v,n) * n;
}

Vector3f refract(const Vector3f& uv, const Vector3f& n, double etai_over_etat) {
    auto cos_theta = fmin(Vector3f::dot(-uv, n), 1.0);
    Vector3f r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vector3f r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.squaredLength())) * n;
    return r_out_perp + r_out_parallel;
}

Vector3f random_in_unit_disk() {
    while (true) {
        auto p = Vector3f(random_double(-1,1), random_double(-1,1), 0);
        if (p.squaredLength() >= 1) 
            continue;
        return p;
    }
}

#endif