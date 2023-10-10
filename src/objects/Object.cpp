#include "Object.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>

Object::Object(){}

Object::~Object(){}

// to check for copy constructors
Object::Object (Object &t){
    std::cout << "OBJECT COPY CONSTRUCTOR CALLED" << std::endl;
}