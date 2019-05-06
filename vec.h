#ifndef _VEC_H_
#define _VEC_H_

struct vec4
{
   double x;
   double y;
   double z;
   double w;

   vec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

   vec4(double _x, double _y, double _z) :
      x(_x),
      y(_y),
      z(_z),
      w(1.0) {}

   vec4(double _x, double _y, double _z, double _w) :
      x(_x),
      y(_y),
      z(_z),
      w(_w) {}

};

vec4 normalise(const vec4 &a);
vec4 add(const vec4 &a, const vec4 &b);
vec4 sub(const vec4 &a, const vec4 &b);
double dot(const vec4 &a, const vec4 &b);
vec4 cross(const vec4 &a, const vec4 &b);
#endif
