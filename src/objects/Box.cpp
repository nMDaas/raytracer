#include "Box.h"
#include <iostream>

Box::Box(){}

Box::~Box(){}

// to check for copy constructors
Box::Box (Box &t){
    std::cout << "BOX COPY CONSTRUCTOR CALLED" << std::endl;
}

bool Box::calcTime(glm::vec4 s, glm::vec4 v) {
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
}

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