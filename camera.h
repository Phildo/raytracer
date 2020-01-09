#ifndef CAMERA_H
#define CAMERA_H

#include "precision.h"
#include "ray3.h"
#include "util.h"

struct camera
{
public:
  camera(vec3 lookfrom, vec3 lookat, vec3 up, precision vfov, precision aspect, precision aperture, precision focus_dist)
  {
    lens_radius = aperture/2;
    precision theta = vfov*3.1415/180;
    precision half_height = tan(theta/2);
    precision half_width = aspect * half_height;

    w = unit_vector(lookfrom-lookat);
    u = unit_vector(cross(up,w));
    v = cross(w,u);

    origin = lookfrom;
    ll = origin
      - half_width*focus_dist*u
      - half_height*focus_dist*v
      - focus_dist*w;
    horiz = 2*half_width*focus_dist*u;
    vert = 2*half_height*focus_dist*v;
  }
  ray3 get_ray3(precision s, precision t)
  {
    vec3 rd = lens_radius*random_in_unit_disk();
    vec3 offset = u*rd.x() + v*rd.y();
    return ray3(origin + offset, ll + s*horiz + t*vert - origin - offset);
  }

  vec3 ll;
  vec3 horiz;
  vec3 vert;
  vec3 origin;
  vec3 u,v,w;
  precision lens_radius;
};

#endif //CAMERA_H

