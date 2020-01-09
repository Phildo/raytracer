#ifndef HITTABLE_H
#define HITTABLE_H

#include "precision.h"
#include "ray3.h"
#include "vec3.h"

class material;

struct hit_record
{
  precision t;
  vec3 p;
  vec3 normal;
  material *mat_ptr;
};

class hittable
{
public:
  virtual bool hit(const ray3& r, precision t_min, precision t_max, hit_record& rec) const = 0;
};

#endif //HITTABLE_H

