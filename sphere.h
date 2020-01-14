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
  sphere(vec3 c, precision r, material *m) : center(c), radius(r), mat_ptr(m) {}
  virtual bool hit(const ray3& r, precision t_min, precision t_max, hit_record& rec) const;
  virtual bool bounding_box(precision t0, precision t1, aabb& box) const;
  vec3 center;
  precision radius;
  material *mat_ptr;
};

#endif //SPHERE_H

