#include "world.h"

#include "vec3.h"
#include "ray3.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"
#include "material.h"
#include "camera.h"
#include "util.h"

vec3 color(ray3 r, hittable *world, int depth)
{
  hit_record rec;
  if(world->hit(r, 0.001, MAXFLOAT, rec))
  {
    ray3 scattered;
    vec3 attenuation;
    if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation*color(scattered,world,depth+1);
    return vec3(0,0,0);
  }
  //background
  vec3 unit_direction = unit_vector(r.direction());
  precision t = 0.5*(unit_direction.y() + 1.0);
  return (1.0-t)*vec3(1,1,1)+t*vec3(0.5,0.7,1.0);
}

void gen_img(canvas img)
{
  hittable *list[5];
  list[0] = new sphere(vec3( 0,     0,-1), 0.5, new lambertian(vec3(0.8,0.3,0.3)));
  list[1] = new sphere(vec3( 0,-100.5,-1), 100, new lambertian(vec3(0.8,0.8,0.0)));
  list[2] = new sphere(vec3( 1,     0,-1), 0.5, new metal(     vec3(0.8,0.6,0.2), 0.3));
  list[3] = new sphere(vec3(-1,     0,-1), 0.5, new dielectric(1.5));
  list[4] = new sphere(vec3(-1,     0,-1), -0.45, new dielectric(1.5));
  hittable *world = new hittable_list(list,5);

  vec3 lookfrom(3,3,2);
  vec3 lookat(0,0,-1);
  precision dist_to_focus = (lookfrom-lookat).length();
  precision aperture = 0;

  camera cam(lookfrom,lookat,vec3(0,1,0),20,(precision)img.w/img.h, aperture, dist_to_focus);

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
        ray3 r = cam.get_ray3(u+random_double()*u_wiggle,v+random_double()*v_wiggle);
        img.px[i] += color(r, world, 0);
      }
      img.px[i] /= samples;
      i++;
    }
  }
}

