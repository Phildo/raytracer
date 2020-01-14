#include "moving_sphere.h"

bool moving_sphere::hit(const ray3& r, precision t_min, precision t_max, hit_record& rec) const
{
  vec3 c2o = r.origin()-center(r.time);
  precision a = dot(r.direction(), r.direction());
    //precision b = 2.0*dot(c2o,r.direction()); //2 optimized out
  precision b = dot(c2o,r.direction());
  precision c = dot(c2o,c2o)-radius*radius;
  //(unoptimized) abc = coefficients of quadratic
    //precision discriminant = b*b - 4*a*c; //2s and 4 optimized out
  precision discriminant = b*b - a*c;
  if(discriminant > 0)
  {
    precision sqrtd = sqrt(discriminant);
    precision t;
    //near root
      //t = (-b - sqrtd) / (2*a); //2s optimized out
    t = (-b - sqrtd) / a;
    if(t < t_max && t > t_min)
    {
      rec.t = t;
      rec.p = r.point_at_parameter(t);
      rec.normal = (rec.p-center(r.time))/radius; //normalized!
      rec.mat_ptr = mat_ptr;
      return true;
    }
    //far root
      //t = (-b + sqrtd) / (2*a); //2s optimized out
    t = (-b + sqrtd) / a;
    if(t < t_max && t > t_min)
    {
      rec.t = t;
      rec.p = r.point_at_parameter(t);
      rec.normal = (rec.p-center(r.time))/radius; //normalized!
      rec.mat_ptr = mat_ptr;
      return true;
    }
  }
  return false;
}

vec3 moving_sphere::center(precision time) const
{
  return center0+((time-time0)/(time1-time0))*(center1-center0);
}

