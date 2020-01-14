#ifndef AABB_H
#define AABB_H

#include "precision.h"
#include "util.h"
#include "vec3.h"
#include "ray3.h"

class aabb
{
public:
  aabb(){}
  aabb(const vec3& a, const vec3& b) { min = a; max = b; }

  /*
  bool hit(const ray3& r, precision tmin, precision tmax) const
  {
    for(int a = 0; a < 3; a++)
    {
      precision mina = (min[a] - r.origin()[a]) / r.direction()[a];
      precision maxa = (max[a] - r.origin()[a]) / r.direction()[a];
      precision t0;
      precision t1;
      if(mina < maxa)
      {
        t0 = mina;
        t1 = maxa;
      }
      else
      {
        t0 = maxa;
        t1 = mina;
      }
      tmin = ffmax(t0, tmin);
      tmax = ffmin(t1, tmax);
      if(tmax <= tmin) return false;
    }
    return true;
  }
  */

  //pixar/andrew kensler
  bool hit(const ray3& r, precision tmin, precision tmax) const
  {
    for(int a = 0; a < 3; a++)
    {
      precision invD = (precision)1.0/r.direction()[a];
      precision t0 = (min[a] - r.origin()[a]) * invD;
      precision t1 = (max[a] - r.origin()[a]) * invD;
      if(invD < 0)
      {
        precision tmp = t0;
        t0 = t1;
        t1 = tmp;
      }
      tmin = t0 > tmin ? t0 : tmin;
      tmax = t1 > tmax ? t1 : tmax;
      if(tmax <= tmin) return false;
    }
    return true;
  }

  vec3 min;
  vec3 max;
};

inline aabb surrounding_box(aabb box0, aabb box1)
{
  vec3 min(
    ffmin(box0.min.x(), box1.min.x()),
    ffmin(box0.min.y(), box1.min.y()),
    ffmin(box0.min.z(), box1.min.z())
    );
  vec3 max(
    ffmax(box0.max.x(), box1.max.x()),
    ffmax(box0.max.y(), box1.max.y()),
    ffmax(box0.max.z(), box1.max.z())
    );
  return aabb(min,max);
}

#endif //AABB_H

