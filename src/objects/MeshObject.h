#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <glm/glm.hpp>

#include <vector>

#include "Triangle.h"

/* This object is for non primitive objects that are made up of triangles */
class MeshObject {
    public:
        MeshObject();
        ~MeshObject();

        MeshObject (MeshObject &t); // to check for copy constructors

        void setTriangles(std::vector<Triangle>* in_triangles);
        void printTriangles();
    private:
        std::vector<Triangle> triangles;
};

#endif