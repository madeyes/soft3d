#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "vec.h"
#include "math.h"

struct matrix4x4
{
    /* Column major. */
    /* 0   4    8   12
     * 1   5    9   13
     * 2   6   10   14
     * 3   7   11   15 */
    double elements[16];

    matrix4x4()
        : elements {0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0} {};

    /* Constructor is row major. */
    matrix4x4(double a00, double a01, double a02, double a03,
              double a10, double a11, double a12, double a13,
              double a20, double a21, double a22, double a23,
              double a30, double a31, double a32, double a33)
        : elements {a00, a10, a20, a30,
                    a01, a11, a21, a31,
                    a02, a12, a22, a32,
                    a03, a13, a23, a33} {};
};

matrix4x4 identity();
vec4 multiply(vec4 v, matrix4x4 m);
matrix4x4 multiply(matrix4x4 M1, matrix4x4 M2);
matrix4x4 rot_x(double angle);
matrix4x4 rot_y(double angle);
matrix4x4 rot_z(double angle);
matrix4x4 translate(double tx, double ty, double tz);
matrix4x4 look_at_rh(const vec4 &eye, const vec4 &target, const vec4 &up);
#endif