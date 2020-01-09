#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include "precision.h"

class vec3
{
  public:
  vec3() {}
  vec3(precision e0, precision e1, precision e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
  precision e[3];
  inline precision x() const { return e[0]; }
  inline precision y() const { return e[1]; }
  inline precision z() const { return e[2]; }
  inline precision r() const { return e[0]; }
  inline precision g() const { return e[1]; }
  inline precision b() const { return e[2]; }
  inline const vec3& operator+() const { return *this; }
  inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  inline precision operator[](int i) const { return e[i]; }
  inline precision& operator[](int i) { return e[i]; }
  inline vec3& operator+=(const vec3 &v2);
  inline vec3& operator-=(const vec3 &v2);
  inline vec3& operator*=(const vec3 &v2);
  inline vec3& operator/=(const vec3 &v2);
  inline vec3& operator*=(const precision t);
  inline vec3& operator/=(const precision t);
  inline precision length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
  inline precision squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
  inline void make_unit_vector();
};

/*
inline std::istream& operator>>(std::istream &is, vec3 &t)
{
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t)
{
  os << t.e[0] << " " << t.e[1] << " " << t.e[2];
  return os;
}
*/

inline void vec3::make_unit_vector()
{
  precision k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
  e[0] *= k; e[1] *= k; e[2] *= k;
}
inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}
inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
inline vec3 operator*(precision t, const vec3 &v)
{
  return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
inline vec3 operator*(const vec3 &v, precision t)
{
  return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}
inline vec3 operator/(vec3 v, precision t)
{
  return vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}
inline precision dot(const vec3 &v1, const vec3 &v2)
{
  return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}
inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1], v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2], v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}
inline vec3& vec3::operator+=(const vec3 &v)
{
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  return *this;
}
inline vec3& vec3::operator-=(const vec3& v)
{
  e[0] -= v.e[0];
  e[1] -= v.e[1];
  e[2] -= v.e[2];
  return *this;
}
inline vec3& vec3::operator*=(const vec3 &v)
{
  e[0] *= v.e[0];
  e[1] *= v.e[1];
  e[2] *= v.e[2];
  return *this;
}
inline vec3& vec3::operator*=(const precision t)
{
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}
inline vec3& vec3::operator/=(const vec3 &v)
{
  e[0] /= v.e[0];
  e[1] /= v.e[1];
  e[2] /= v.e[2];
  return *this;
}
inline vec3& vec3::operator/=(const precision t)
{
  precision k = 1.0/t;
  e[0] *= k;
  e[1] *= k;
  e[2] *= k;
  return *this;
}
inline vec3 unit_vector(vec3 v)
{
  return v / v.length();
}

#endif //VEC3_H

