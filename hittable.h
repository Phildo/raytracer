#ifndef HITTABLE_H
#define HITTABLE_H

#include "precision.h"
#include "util.h"
#include "ray3.h"
#include "vec3.h"
#include "aabb.h"

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
  virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
};

#endif //HITTABLE_H

