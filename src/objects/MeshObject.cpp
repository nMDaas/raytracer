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
    for (int i = 0; i < triangles.size(); i++) {
        if (triangles[i].calcTimes(s,v)) {
            t = triangles[i].getTime();
            return true;
        }
    }
  }


float MeshObject::getTime() {
   return t;
}