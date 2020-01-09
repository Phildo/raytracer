#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "precision.h"
#include "ray3.h"
#include "vec3.h"

class sphere: public hittable
{
public:
  sphere() {}
  sphere(vec3 c, precision r) : center(c), radius(r) {}
  virtual bool hit(const ray3& r, precision t_min, precision t_max, hit_record& rec) const;
  vec3 center;
  precision radius;
};

#endif //SPHERE_H

