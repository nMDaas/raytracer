#include "Box.h"
#include <iostream>

Box::Box(){}

Box::~Box(){}

// to check for copy constructors
Box::Box (Box &t){
    std::cout << "BOX COPY CONSTRUCTOR CALLED" << std::endl;
}