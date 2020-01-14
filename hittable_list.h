#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

class hittable_list: public hittable
{
public:
  hittable_list() {}
  hittable_list(hittable **l, int n) {list = l; list_size = n;}
  virtual bool hit(const ray3& r, precision t_min, precision t_max, hit_record& rec) const;
  virtual bool bounding_box(precision t0, precision t1, aabb& box) const;
  hittable **list;
  int list_size;
};

#endif //HITTABLE_LIST_H

