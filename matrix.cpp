#include "vec.h"
#include "matrix.h"
#include <stdio.h>

/* Treats vector v as a row vector - multiplication is vM */
vec4 multiply(vec4 v, matrix4x4 M)
{
    vec4 result;
    result.x = (M.elements[0] * v.x) + (M.elements[1] * v.y) + (M.elements[2] * v.z + M.elements[3] * v.w);
    result.y = (M.elements[4] * v.x) + (M.elements[5] * v.y) + (M.elements[6] * v.z + M.elements[7] * v.w);
    result.z = (M.elements[8] * v.x) + (M.elements[9] * v.y) + (M.elements[10] * v.z + M.elements[11] * v.w);
    result.w = (M.elements[12] * v.x) + (M.elements[13] * v.y) + (M.elements[14] * v.z + M.elements[15] * v.w);
    return result;
}

matrix4x4 multiply(matrix4x4 M1, matrix4x4 M2)
{
    matrix4x4 result;
    result.elements[0] = (M1.elements[0] * M2.elements[0]) + (M1.elements[4] * M2.elements[1]) +
                         (M1.elements[8] * M2.elements[2]) + (M1.elements[12] * M2.elements[3]);
    result.elements[1] = (M1.elements[1] * M2.elements[0]) + (M1.elements[5] * M2.elements[1]) +
                         (M1.elements[9] * M2.elements[2]) + (M1.elements[13] * M2.elements[3]);
    result.elements[2] = (M1.elements[2] * M2.elements[0]) + (M1.elements[6] * M2.elements[1]) +
                         (M1.elements[10] * M2.elements[2]) + (M1.elements[14] * M2.elements[3]);
    result.elements[3] = (M1.elements[3] * M2.elements[0]) + (M1.elements[7] * M2.elements[1]) +
                         (M1.elements[11] * M2.elements[2]) + (M1.elements[15] * M2.elements[3]);
    result.elements[4] = (M1.elements[0] * M2.elements[4]) + (M1.elements[4] * M2.elements[5]) +
                         (M1.elements[8] * M2.elements[6]) + (M1.elements[12] * M2.elements[7]);
    result.elements[5] = (M1.elements[1] * M2.elements[4]) + (M1.elements[5] * M2.elements[5]) +
                         (M1.elements[9] * M2.elements[6]) + (M1.elements[13] * M2.elements[7]);
    result.elements[6] = (M1.elements[2] * M2.elements[4]) + (M1.elements[6] * M2.elements[5]) +
                         (M1.elements[10] * M2.elements[6]) + (M1.elements[14] * M2.elements[7]);
    result.elements[7] = (M1.elements[3] * M2.elements[4]) + (M1.elements[7] * M2.elements[5]) +
                         (M1.elements[11] * M2.elements[6]) + (M1.elements[15] * M2.elements[7]);
    result.elements[8] = (M1.elements[0] * M2.elements[8]) + (M1.elements[4] * M2.elements[9]) +
                         (M1.elements[8] * M2.elements[10]) + (M1.elements[12] * M2.elements[11]);
    result.elements[9] = (M1.elements[1] * M2.elements[8]) + (M1.elements[5] * M2.elements[9]) +
                         (M1.elements[9] * M2.elements[10]) + (M1.elements[13] * M2.elements[11]);
    result.elements[10] = (M1.elements[2] * M2.elements[8]) + (M1.elements[6] * M2.elements[9]) +
                         (M1.elements[10] * M2.elements[10]) + (M1.elements[14] * M2.elements[11]);
    result.elements[11] = (M1.elements[3] * M2.elements[8]) + (M1.elements[7] * M2.elements[9]) +
                         (M1.elements[11] * M2.elements[10]) + (M1.elements[15] * M2.elements[11]);
    result.elements[12] = (M1.elements[0] * M2.elements[12]) + (M1.elements[4] * M2.elements[13]) +
                         (M1.elements[8] * M2.elements[14]) + (M1.elements[12] * M2.elements[15]);
    result.elements[13] = (M1.elements[1] * M2.elements[12]) + (M1.elements[5] * M2.elements[13]) +
                         (M1.elements[9] * M2.elements[14]) + (M1.elements[13] * M2.elements[15]);
    result.elements[14] = (M1.elements[2] * M2.elements[12]) + (M1.elements[6] * M2.elements[13]) +
                         (M1.elements[10] * M2.elements[14]) + (M1.elements[14] * M2.elements[15]);
    result.elements[15] = (M1.elements[3] * M2.elements[12]) + (M1.elements[7] * M2.elements[13]) +
                         (M1.elements[11] * M2.elements[14]) + (M1.elements[15] * M2.elements[15]);
    return result;
}

matrix4x4 rot_x(double angle)
{
    double cos_ang = cos(angle);
    double sin_ang = sin(angle);
    return matrix4x4(1.0,     0.0,     0.0, 0.0,
                     0.0, cos_ang, sin_ang, 0.0,
                     0.0,-sin_ang, cos_ang, 0.0,
                     0.0,     0.0,     0.0, 1.0);
}

matrix4x4 rot_y(double angle)
{
    double cos_ang = cos(angle);
    double sin_ang = sin(angle);
    return matrix4x4( cos_ang, 0.0, -sin_ang, 0.0,
                          0.0, 1.0,      0.0, 0.0,
                      sin_ang, 0.0,  cos_ang, 0.0,
                          0.0, 0.0,      0.0, 1.0);
}

matrix4x4 rot_z(double angle)
{
    double cos_ang = cos(angle);
    double sin_ang = sin(angle);
    return matrix4x4( cos_ang, sin_ang, 0.0, 0.0,
                     -sin_ang, cos_ang, 0.0, 0.0,
                          0.0,     0.0, 1.0, 0.0,
                          0.0,     0.0, 0.0, 1.0);
}

matrix4x4 translate(double tx, double ty, double tz)
{
    return matrix4x4(1.0, 0.0, 0.0, 0.0,
                     0.0, 1.0, 0.0, 0.0,
                     0.0, 0.0, 1.0, 0.0,
                      tx,  ty,  tz, 1.0);
}

matrix4x4 identity()
{
    return matrix4x4(1.0, 0.0, 0.0, 0.0,
                     0.0, 1.0, 0.0, 0.0,
                     0.0, 0.0, 1.0, 0.0,
                     0.0, 0.0, 0.0, 1.0);
}

matrix4x4 look_at_rh(const vec4 &eye, const vec4 &target, const vec4 &up)
{
    vec4 z_axis = normalise(sub(eye, target));
    vec4 x_axis = normalise(cross(up, z_axis));
    vec4 y_axis = cross(z_axis, x_axis);

    // Create a 4x4 orientation matrix from the right, up, and forward vectors
    // This is transposed which is equivalent to performing an inverse 
    // if the matrix is orthonormalized (in this case, it is).
    return multiply(matrix4x4(x_axis.x, y_axis.x, z_axis.x, 0.0,
                              x_axis.y, y_axis.y, z_axis.y, 0.0,
                              x_axis.z, y_axis.z, z_axis.z, 0.0,
                              0.0,      0.0,      0.0, 1.0),
                    matrix4x4(1.0, 0.0, 0.0, 0.0,
                              0.0, 1.0, 0.0, 0.0,
                              0.0, 0.0, 1.0, 0.0,
                              -eye.x, -eye.y, -eye.z, 1.0));
}