#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "hittable.h"
#include "precision.h"
#include "ray3.h"
#include "vec3.h"

class moving_sphere: public hittable
{
public:
  moving_sphere() {}
  moving_sphere(vec3 c0, vec3 c1, precision t0, precision t1, precision r, material *m) : center0(c0), center1(c1), time0(t0), time1(t1), radius(r), mat_ptr(m) {}
  virtual bool hit(const ray3& r, precision t_min, precision t_max, hit_record& rec) const;
  //virtual bool bounding_box(precision t0, precision t1, aabb& box) const;
  vec3 center(precision time) const;
  vec3 center0, center1;
  precision time0, time1;
  precision radius;
  material *mat_ptr;
};

#endif //MOVING_SPHERE_H

