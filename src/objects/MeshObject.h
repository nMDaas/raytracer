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

        void addTriangle(glm::vec4 v0, glm::vec4 v1, glm::vec4 v2);
        void printTriangles();
    private:
        std::vector<Triangle> triangles;
};

#endif