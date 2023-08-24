#include "Cylinder.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

Cylinder::Cylinder(){}

Cylinder::~Cylinder(){}

// to check for copy constructors
Cylinder::Cylinder (Cylinder &t){
    std::cout << "CYLINDER COPY CONSTRUCTOR CALLED" << std::endl;
}

// calculates tmin and tmax of a ray's intersection with a unit box
bool Cylinder::calcTimes(glm::vec4 s, glm::vec4 v) {
    spdlog::debug("In Cylinder::calcTimes()");
    spdlog::debug("s: " + glm::to_string(s));
    spdlog::debug("v: " + glm::to_string(v));

    float a = pow(v.z,2) + pow(v.x,2);
    float b = (2 * v.z * s.z) + (2 * v.x * s.x);
    float c = pow(s.z,2) + pow(s.x,2) - 1;

    spdlog::debug("a: " + (int) a); 
    spdlog::debug("b: " + (int) b); 
    spdlog::debug("b: " + (int) c); 

    float discriminant = pow(b,2) - (4 * a * c);
    spdlog::debug("discriminant: " + (int) discriminant);
    if (discriminant < 0) {
        return false;
    }

    tmin = (-b + sqrt(discriminant)) / (2 * a);
    tmax = (-b - sqrt(discriminant)) / (2 * a);

    if (tmin > tmax) {
        std::swap(tmin,tmax);
    }

    float tMinY = (0.0f - s.y)/v.y; 
    float tMaxY = (1.0f - s.y)/v.y; 

    if (tMinY > tMaxY) {
        std::swap(tMinY, tMaxY); 
    }

    // ray missed box
    if ((tmin > tMaxY) || (tMinY > tmax)) {
        return false;
    }

    tmin = (tMinY > tmin) ? tMinY : tmin;
    tmax = (tMaxY < tmax) ? tMaxY : tmax;
    return true;
}

// returns the time of first intersection of the ray with the unit cylinder
float Cylinder::getTime() {
    spdlog::debug("In Cylinder::getTime()");

    // if tmin and tmax are both positive, tmin and tmax both are in front of camera 
    // return smaller value
    if (tmin > 0 && tmax > 0 && tmin <= tmax) {
        return tmin;
    }

    // if tmin is -ve and tmax is +ve, tmin is behind the camera
    // return tmax
    else if (tmin < 0 && tmax > 0) {
        return tmax;
    }

    // no hits - check if you ever reach here
    else {
        return INFINITY; 
    }
    
}

glm::vec4 Cylinder::getNormal(glm::vec4 intersectionPoint) {
}