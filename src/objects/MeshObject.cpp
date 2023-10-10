#include "MeshObject.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>

MeshObject::MeshObject(){}

MeshObject::~MeshObject(){}

// to check for copy constructors
MeshObject::MeshObject (MeshObject &t){
    std::cout << "MESH OBJECT COPY CONSTRUCTOR CALLED" << std::endl;
}

void MeshObject::addTriangle(glm::vec4 v0, glm::vec4 v1, glm::vec4 v2) {
    Triangle triangle(v0,v1,v2);
    triangles.push_back(triangle);
}

 void MeshObject::printTriangles() {
    for (int i = 0; i < triangles.size(); i++) {
        std::cout << "--" << i << "--" << std::endl;
        triangles[i].printTriangleDetails();
        std::cout << "----" << std::endl;
    }
 }