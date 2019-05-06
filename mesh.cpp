#include "mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>

int mesh_from_obj_file(std::string filename, mesh *object)
{
    std::ifstream obj_stream(filename);
    if (!obj_stream.is_open())
    {
        return -1;
    }
    std::string line;
    int err = 0;
    while (std::getline(obj_stream, line))
    {
        std::string type;
        double x, y, z;
        if (line[0] == 'v' && line[1] == ' ')
        {
            std::cout << line << std::endl;
            std::istringstream iss(line);
            if (!(iss >> type >> x >> y >> z))
            {
                err = -1;
                break;
            }
            object->vertices.push_back(vec4(x, y, z, 1.0));
        }
        else if (line[0] == 'f' && line[1] == ' ')
        {
            std::istringstream iss(line);
            std::string face;
            while (std::getline(iss, face, ' '))
            {
                if (face[0] != 'f')
                {
                    std::cout << face.substr(0, face.find('/')) << std::endl;
                }
            }
        }
    }
    obj_stream.close();
    return err;
}