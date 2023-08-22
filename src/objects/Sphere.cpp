#include "Sphere.h"
#include <iostream>

#include <glm/gtx/string_cast.hpp>

Sphere::Sphere(){}

Sphere::~Sphere(){}

// to check for copy constructors
Sphere::Sphere (Sphere &t){
    std::cout << "SPHERE COPY CONSTRUCTOR CALLED" << std::endl;
}

// calculates tmin and tmax of a ray's intersection with a unit sphere
bool Sphere::calcTimes(glm::vec4 s, glm::vec4 v) {
    std::cout << "s: " << glm::to_string(s) << " v: " << glm::to_string(v) << std::endl;
    float r = 1.0f;
    float a = pow(v.x,2) + pow(v.y,2) + pow(v.z,2);
    std::cout << "pow(v.x,2) : " << pow(v.x,2)  << std::endl;
    std::cout << "pow(v.y,2): " << pow(v.y,2) << std::endl;
    std::cout << "pow(v.z,2): " << pow(v.z,2) << std::endl;
    std::cout << "a: " << a << std::endl;
    float b = 2 * ((s.x * v.x) + (s.y * v.y) + (s.z * v.z));
    std::cout << "b: " << b << std::endl;
    float c = pow(s.x,2) + pow(s.y,2) + pow(s.z,2) - pow(r,2);
    std::cout << "c: " << c << std::endl;

    float discriminant = pow(b,2) - (4 * a * c);
    std::cout << "discriminant: " << discriminant << std::endl;
    if (discriminant < 0) {
        return false;
    }

    tmin = (-b + sqrt(discriminant)) / (2 * a);
    tmax = (-b - sqrt(discriminant)) / (2 * a);

    if (tmin > tmax) {
        std::swap(tmin,tmax);
    }

    std::cout << "tmin: " << tmin << " tmax: " << tmax << std::endl;

    return true;
}

// returns the time of first intersection of the ray with the unit sphere
float Sphere::getTime() {
    // if tmin and tmax are both positive, tmin and tmax both are in front of camera 
    // return smaller value
    if (tmin > 0 && tmax > 0 && tmin <= tmax) {
        std::cout << "returning tmin: " << tmin << std::endl;
        return tmin;
    }

    // if tmin is -ve and tmax is +ve, tmin is behind the camera
    // return tmax
    else if (tmin < 0 && tmax > 0) {
        std::cout << "returning tmax" << std::endl;
        return tmax;
    }

    // no hits - check if you ever reach here
    else {
        std::cout << "returning infinity" << std::endl;
        return INFINITY; 
    }
    
}

glm::vec4 Sphere::getNormal(glm::vec4 intersectionPoint) {
    std::cout << "intersection: " << glm::to_string(intersectionPoint) << std::endl;
    glm::vec4 normal = glm::vec4(intersectionPoint.x,intersectionPoint.y,intersectionPoint.z,0);
    std::cout << "normal: " << glm::to_string(normal) << std::endl;
    return normal;
}