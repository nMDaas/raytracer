#include "Box.h"
#include <iostream>

Box::Box(){}

Box::~Box(){}

// to check for copy constructors
Box::Box (Box &t){
    std::cout << "BOX COPY CONSTRUCTOR CALLED" << std::endl;
}

// calculates tmin and tmax of a ray's intersection with a unit box
bool Box::calcTimes(glm::vec4 s, glm::vec4 v) {
    float tMinX = (vmin.x - s.x)/v.x; 
    float tMaxX = (vmax.x - s.x)/v.x;

    // swaps account for different ray directions
    if (tMinX > tMaxX) {
        std::swap(tMinX, tMaxX); 
    }

    float tMinY = (vmin.y - s.y)/v.y; 
    float tMaxY = (vmax.y - s.y)/v.y; 

    if (tMinY > tMaxY) {
        std::swap(tMinY, tMaxY); 
    }

    tmin = (tMinX > tMinY) ? tMinX : tMinY;
    tmax = (tMaxX < tMaxY) ? tMaxX : tMaxY;

    // ray missed box
    if ((tMinX > tMaxY) || (tMinY > tMaxX)) {
        return false;
    } 

    float tMinZ = (vmin.z - s.z)/v.z; 
    float tMaxZ = (vmax.z - s.z)/v.z; 

    if (tMinZ > tMaxZ) {
        std::swap(tMinZ, tMaxZ); 
    }

    // ray missed box
    if ((tmin > tMaxZ) || (tMinZ > tmax)) {
        return false;
    }

    tmin = (tMinZ > tmin) ? tMinZ : tmin;
    tmax = (tMaxZ < tmax) ? tMaxZ : tmax;

    return true;
}

// returns the time of first intersection of the ray with the unit box
float Box::getTime() {
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

glm::vec4 Box::getNormal(glm::vec4 intersectionPoint) {
    glm::vec4 normal(0,0,0,0);

    if ((intersectionPoint.x < 0.5001f) && (intersectionPoint.x > 0.4999f)) {
        normal.x = 1;
    }
    else if ((intersectionPoint.x > -0.5001f) && (intersectionPoint.x < -0.4999f)) {
        normal.x = -1;
    }
    else {
        normal.x = 0;
    }

    if ((intersectionPoint.y < 0.5001f) && (intersectionPoint.y > 0.4999f)) {
        normal.y = 1;
    }
    else if ((intersectionPoint.y > -0.5001f) && (intersectionPoint.y < -0.4999f)) {
        normal.y = -1;
    }
    else {
        normal.y = 0;
    }

    if ((intersectionPoint.z < 0.5001f) && (intersectionPoint.z > 0.4999f)) {
        normal.z = 1;
    }
    else if ((intersectionPoint.z > -0.5001f) && (intersectionPoint.z < -0.4999f)) {
        normal.z = -1;
    }
    else {
        normal.z = 0;
    }

    return normal;
}