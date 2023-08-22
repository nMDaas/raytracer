#include "Sphere.h"
#include <iostream>

Sphere::Sphere(){}

Sphere::~Sphere(){}

// to check for copy constructors
Sphere::Sphere (Sphere &t){
    std::cout << "SPHERE COPY CONSTRUCTOR CALLED" << std::endl;
}