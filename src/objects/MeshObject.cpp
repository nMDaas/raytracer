#include "MeshObject.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>

MeshObject::MeshObject(){}

MeshObject::~MeshObject(){}

// to check for copy constructors
MeshObject::MeshObject (MeshObject &t){
    std::cout << "MESH OBJECT COPY CONSTRUCTOR CALLED" << std::endl;
}