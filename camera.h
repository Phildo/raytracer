#ifndef CAMERA_H
#define CAMERA_H

#include "precision.h"
#include "ray3.h"

struct camera
{
public:
  camera()
  {
    ll = vec3(-2,-1,-1);
    horiz = vec3(4,0,0);
    vert = vec3(0,2,0);
    origin = vec3(0,0,0);
  }
  ray3 get_ray3(precision u, precision v)
  {
    return ray3(origin, ll + u*horiz + v*vert);
  }

  vec3 ll;
  vec3 horiz;
  vec3 vert;
  vec3 origin;
};

#endif //CAMERA_H

