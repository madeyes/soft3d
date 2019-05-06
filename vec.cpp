#include "vec.h"
#include <math.h>

vec4 add(const vec4 &a, const vec4 &b)
{
   return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

vec4 sub(const vec4 &a, const vec4 &b)
{
   return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

double dot(const vec4 &a, const vec4 &b)
{
   return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec4 cross(const vec4 &a, const vec4 &b)
{
   return vec4(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 1.0);
}

vec4 normalise(const vec4 &a)
{
   const double denom = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
   return vec4(a.x / denom, a.y / denom, a.z / denom, a.w);
}
