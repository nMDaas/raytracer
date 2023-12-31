#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <glm/glm.hpp>

#include <vector>
#include <math.h>

#include "Triangle.h"

/* This object is for non primitive objects that are made up of triangles */
class MeshObject {
    public:
        MeshObject();
        ~MeshObject();

        //MeshObject (MeshObject &t); // to check for copy constructors

        void setTriangles(std::vector<Triangle>* in_triangles);
        void printTriangles();

        bool calcTimes(glm::vec4 s, glm::vec4 v); // calculates tmin and tmax of a ray's intersection with the meshObject
        float getTime();
        void transformTriangles(glm::mat4 transform);
        void inverseTransformTriangles(glm::mat4 inverseTransform); // remove modelview.top() transform 

    private:
        std::vector<Triangle> triangles;
        float t;
};

#endif