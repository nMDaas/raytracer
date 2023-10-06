#include "Triangle.h"
#include <iostream>

#include <glm/gtx/string_cast.hpp>

Triangle::Triangle(){}

Triangle::~Triangle(){}

// to check for copy constructors
Triangle::Triangle (Triangle &t){
    std::cout << "TRIANGLE COPY CONSTRUCTOR CALLED" << std::endl;
}

