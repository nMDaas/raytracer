#include "MeshObject.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>

MeshObject::MeshObject(){}

MeshObject::~MeshObject(){}

/* to check for copy constructors
MeshObject::MeshObject (MeshObject &t){
    std::cout << "MESH OBJECT COPY CONSTRUCTOR CALLED" << std::endl;
}*/

void MeshObject::setTriangles(std::vector<Triangle>* in_triangles) {
    std::vector<Triangle> temp = *in_triangles;
    for (int i = 0; i < temp.size(); i++) {
        Triangle t = temp[i];
        triangles.push_back(t);
    }
}

 void MeshObject::printTriangles() {
    std::cout << "traingles size: " << triangles.size() << std::endl;
    for (int i = 0; i < triangles.size(); i++) {
        std::cout << "--" << i << "--" << std::endl;
        triangles[i].printTriangleDetails();
        std::cout << "----" << std::endl;
    }
 }

  bool MeshObject::calcTimes(glm::vec4 s, glm::vec4 v) {
    t = INFINITY;
    for (int i = 0; i < triangles.size(); i++) {
        if (triangles[i].calcTimes(s,v)) {
            float newTime = triangles[i].getTime();
            if (newTime < t) {
                t = newTime;
            }
        }
    }

    return !isinf(t);
  }


float MeshObject::getTime() {
   return t;
}

void  MeshObject::transformTriangles(glm::mat4 transform) {
    for (int i = 1; i < triangles.size(); i++) {
        triangles[i].applyTransform(transform);
    }
}

void MeshObject::inverseTransformTriangles(glm::mat4 inverseTransform) {
    for (int i = 1; i < triangles.size(); i++) {
        triangles[i].applyTransform(inverseTransform);
    }
}