#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include "vec3.h"

inline double random_double()
{
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double_sqr()
{
  return random_double()*random_double();
}

vec3 random_in_unit_sphere()
{
  vec3 p;
  do
  {
  p = 2.0*vec3(random_double(),random_double(),random_double())-vec3(1,1,1);
  } while(p.squared_length() >= 1.0);
  return p;
}

vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0*vec3(random_double(),random_double(),0) - vec3(1,1,0);
    } while (dot(p,p) >= 1.0);
    return p;
}

vec3 reflect(const vec3& v, const vec3& n)
{
  return v - 2*dot(v,n)*n;
}

bool refract(const vec3& v, const vec3& n, precision ni_over_nt, vec3& refracted)
{
  vec3 uv = unit_vector(v);
  precision dt = dot(uv,n);
  precision discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
  if(discriminant > 0)
  {
    refracted = ni_over_nt * (uv - n*dt) - n*sqrt(discriminant);
    return true;
  }
  return false;
}

precision schlick(precision cosine, precision ref_idx)
{
  precision r0 = (1-ref_idx) / (1+ref_idx);
  r0 = r0*r0;
  return r0 + (1-r0)*pow((1-cosine),5);
}

#endif //UTIL_H

