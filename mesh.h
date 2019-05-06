#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <string>
#include <stdint.h>

#include "vec.h"
#include "matrix.h"

struct mesh
{
    std::vector<vec4> vertices;
    std::vector<uint8_t> indices;
    matrix4x4 transform;
};

int mesh_from_obj_file(std::string filename, mesh* object);
#endif