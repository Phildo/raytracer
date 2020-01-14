#ifndef MATERIAL_H
#define MATERIAL_H

#include "precision.h"
#include "util.h"
#include "vec3.h"
#include "ray3.h"

class material
{
public:
  virtual bool scatter(const ray3& r_in, const hit_record& rec, vec3& attenuation, ray3& scattered) const = 0;
};

class lambertian : public material
{
public:
  lambertian(const vec3& a) : albedo(a) {}
  virtual bool scatter(const ray3& r_in, const hit_record& rec, vec3& attenuation, ray3& scattered) const
  {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = ray3(rec.p,target-rec.p, r_in.time);
    attenuation = albedo;
    return true;
  }
  vec3 albedo;
};

class metal : public material
{
public:
  metal(const vec3& a, precision f) : albedo(a)
  {
    if(f < 1) fuzz = f; else fuzz = 1;
  }

  virtual bool scatter(const ray3& r_in, const hit_record& rec, vec3& attenuation, ray3& scattered) const
  {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray3(rec.p,reflected + fuzz*random_in_unit_sphere(), r_in.time);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }
  vec3 albedo;
  precision fuzz;
};

class dielectric : public material
{
public:
  dielectric(precision ri) : ref_idx(ri) {}

  virtual bool scatter(const ray3& r_in, const hit_record& rec, vec3& attenuation, ray3& scattered) const
  {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);

    precision ni_over_nt;
    attenuation = vec3(1,1,1);
    vec3 refracted;

    precision reflect_prob;
    precision cosine;

    if(dot(r_in.direction(), rec.normal) > 0)
    {
      outward_normal = -rec.normal;
      ni_over_nt = ref_idx;
      cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    else
    {
      outward_normal = rec.normal;
      ni_over_nt = 1.0/ref_idx;
      cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }

    if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
      reflect_prob = schlick(cosine, ref_idx);
    else reflect_prob = 1;

    if(random_double() < reflect_prob)
      scattered = ray3(rec.p, reflected, r_in.time);
    else
      scattered = ray3(rec.p, refracted, r_in.time);

    return true;
  }
  precision ref_idx;
};

#endif //MATERIAL_H

