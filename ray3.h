#ifndef RAY3_H
#define RAY3_H

#include "precision.h"
#include "vec3.h"

class ray3
{
  public:
  ray3() {}
  ray3(const vec3 &a, const vec3 &b) { A = a; B = b; }
  inline vec3 origin()    const { return A; }
  inline vec3 direction() const { return B; }
  inline vec3 point_at_parameter(precision t) const { return A + t*B; }

  vec3 A;
  vec3 B;
};

#endif //RAY3_H

