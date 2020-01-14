#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "hittable.h"
#include "precision.h"
#include "vec3.h"
#include "ray3.h"

class bvh_node : public hittable
{
public:
  bvh_node() {}
  bvh_node(hittable **l, int n, precision time0, precision time1);

  virtual bool hit(const ray3& r, precision tmin, precision tmax, hit_record& rect) const;
  virtual bool bounding_box(precision t0, precision t1, aabb& box) const;
  
  hittable *left;
  hittable *right;
  aabb box;
};

#endif //BVH_NODE_H

