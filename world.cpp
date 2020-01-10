#include "world.h"

#include "vec3.h"
#include "ray3.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"
#include "material.h"
#include "camera.h"
#include "util.h"

vec3 color(ray3 r, hittable *world, int depth, int maxdepth)
{
  hit_record rec;
  #ifdef _WIN32
  if(world->hit(r, 0.001, 10000.0, rec))
  #else
  if(world->hit(r, 0.001, MAXFLOAT, rec))
  #endif
  {
    ray3 scattered;
    vec3 attenuation;
    if(depth < maxdepth && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation*color(scattered,world,depth+1,maxdepth);
    return vec3(0,0,0);
  }
  //background
  vec3 unit_direction = unit_vector(r.direction());
  precision t = 0.5*(unit_direction.y() + 1.0);
  return (1.0-t)*vec3(1,1,1)+t*vec3(0.5,0.7,1.0);
}

void gen_img(canvas img, int aa, int bounces)
{
  hittable **list;
  hittable *world;
  camera cam;

  /*
  //Simple world (3 balls, one diffuse, one rough metal, one 'bubble')
  {
    list = new hittable*[5];
    list[0] = new sphere(vec3( 0,     0,-1), 0.5, new lambertian(vec3(0.8,0.3,0.3)));
    list[1] = new sphere(vec3( 0,-100.5,-1), 100, new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3( 1,     0,-1), 0.5, new metal(     vec3(0.8,0.6,0.2), 0.3));
    list[3] = new sphere(vec3(-1,     0,-1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1,     0,-1), -0.45, new dielectric(1.5));
    world = new hittable_list(list,5);

    vec3 lookfrom(3,3,2);
    vec3 lookat(0,0,-1);
    precision dist_to_focus = (lookfrom-lookat).length();
    precision aperture = 0;

    cam = camera(lookfrom,lookat,vec3(0,1,0),20,(precision)img.w/img.h, aperture, dist_to_focus);
  }
  //*/

  //*
  //Final image in "Ray Tracing in One Weekend"
  {
    int n = 500;
    int iter = sqrt(n-1-3)-1; //-1 for earth, -3 for bigballs, final -1 for guaranteed space

    list = new hittable*[n+1];
    list[0] = new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5,0.5,0.5)));
    int i = 1;
    for(int a = -iter/2; a < iter/2; a++)
    {
      for(int b = -iter/2; b < iter/2; b++)
      {
        precision choose_mat = random_double();
        vec3 center(a+0.9*random_double(),0.2,b+0.9*random_double());
        if((center-vec3(4,0.2,0)).length() > 0.9)
        {
          if(choose_mat < 0.8)
            list[i++] = new sphere(center, 0.2, new lambertian(vec3(random_double_sqr(),random_double_sqr(),random_double_sqr())));
          else if(choose_mat < 0.95)
            list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1+random_double()),0.5*(1+random_double()),0.5*(1+random_double())),0.5*random_double()));
          else
            list[i++] = new sphere(center, 0.2, new dielectric(1.5));
        }
      }
    }

    list[i++] = new sphere(vec3( 0,1,0), 1, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4,1,0), 1, new lambertian(vec3(0.4,0.2,0.1)));
    list[i++] = new sphere(vec3( 4,1,0), 1, new metal(vec3(0.7,0.6,0.1),0.0));
    world = new hittable_list(list,i);

    vec3 lookfrom(8,4,4);
    vec3 lookat(0,0,-1);
    precision dist_to_focus = (lookfrom-lookat).length();
    precision aperture = 0.1;

    cam = camera(lookfrom,lookat,vec3(0,1,0),40,(precision)img.w/img.h, aperture, dist_to_focus);
  }
  //*/

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
      for(int s = 0; s < aa; s++)
      {
        ray3 r = cam.get_ray3(u+random_double()*u_wiggle,v+random_double()*v_wiggle);
        img.px[i] += color(r, world, 0, bounces);
      }
      img.px[i] /= aa;
      i++;
    }
  }
}

