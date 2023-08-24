#include "Cylinder.h"

#include <iostream>

Cylinder::Cylinder(){}

Cylinder::~Cylinder(){}

// to check for copy constructors
Cylinder::Cylinder (Cylinder &t){
    std::cout << "CYLINDER COPY CONSTRUCTOR CALLED" << std::endl;
}

// calculates tmin and tmax of a ray's intersection with a unit box
bool Cylinder::calcTimes(glm::vec4 s, glm::vec4 v) {
}
float Cylinder::getTime() {
}

glm::vec4 Cylinder::getNormal(glm::vec4 intersectionPoint) {
}