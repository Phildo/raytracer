#include "world.h"

#include "vec3.h"
#include "ray3.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

vec3 color(ray3 r, hittable *world)
{
  hit_record rec;
  if(world->hit(r, 0, MAXFLOAT, rec))
    return 0.5*rec.normal+vec3(0.5,0.5,0.5);
  //background
  vec3 unit_direction = unit_vector(r.direction());
  precision t = 0.5*(unit_direction.y() + 1.0);
  return (1.0-t)*vec3(1,1,1)+t*vec3(0.5,0.7,1.0);
}

void gen_img(canvas img)
{
  hittable *list[2];
  list[0] = new sphere(vec3(0,0,-1),0.5);
  list[1] = new sphere(vec3(0,-100.5,-1),100);
  hittable *world = new hittable_list(list,2);

  camera cam;
  int samples = 100;
  precision u_wiggle = (precision)1/img.w;
  precision v_wiggle = (precision)1/img.h;

  int i = 0;
  for(int y = 0; y < img.h; y++) //0 = top
  {
    for(int x = 0; x < img.w; x++) //0 = left
    {
      precision u = (precision)x/img.w; //0 = left
      precision v = 1.-(precision)y/img.h; //0 = bottom
      img.px[i] = vec3(0,0,0);
      for(int s = 0; s < samples; s++)
      {
        ray3 r = cam.get_ray(u+random_double()*u_wiggle,v+random_double()*v_wiggle);
        img.px[i] += color(r, world);
      }
      img.px[i] /= samples;
      i++;
    }
  }
}

