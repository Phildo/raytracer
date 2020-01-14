#ifndef UTIL_H
#define UTIL_H

#include "precision.h"
#include "vec3.h"

double random_double();
double random_double_sqr();
vec3 random_in_unit_sphere();
vec3 random_in_unit_disk();
vec3 reflect(const vec3& v, const vec3& n);
bool refract(const vec3& v, const vec3& n, precision ni_over_nt, vec3& refracted);
precision schlick(precision cosine, precision ref_idx);
precision ffmin(precision a, precision b);
precision ffmax(precision a, precision b);

#endif //UTIL_H

