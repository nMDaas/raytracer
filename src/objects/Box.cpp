#include "Box.h"
#include <iostream>

#include <glm/gtx/string_cast.hpp>

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

glm::vec2 Box::getTextureCoordinates(glm::vec4 intersectionPoint) {
    float absX = abs(intersectionPoint.x);
    float absY = abs(intersectionPoint.y);
    float absZ = abs(intersectionPoint.z);

    /*
    std::cout << "intersectionPoint: " << glm::to_string(intersectionPoint) << std::endl;
    std::cout << "absX: " << absX << std::endl;
    std::cout << "absY: " << absY << std::endl;
    std::cout << "absZ: " << absZ << std::endl;
    */

    // intersectionPoint is on front face
    if (absZ >= absY && absZ >= absX && intersectionPoint.z >= 0) {
        return calcTextureCoordinates(intersectionPoint.x,intersectionPoint.y,glm::vec2(0.25f,0.25f));
    }
    // intersectionPoint is on back face
    else if (absZ >= absY && absZ >= absX && intersectionPoint.z < 0) {
        return calcTextureCoordinates(intersectionPoint.x,intersectionPoint.y,glm::vec2(0.75f,0.25f));
    }
    // intersectionPoint is on left face
    else if (absX >= absY && absX >= absZ && intersectionPoint.x < 0) {
        return calcTextureCoordinates(intersectionPoint.z,intersectionPoint.y,glm::vec2(0.0f,0.25f));
    }
    // intersectionPoint is on right face
    else if (absX >= absY && absX >= absZ && intersectionPoint.x >= 0) {
        return calcTextureCoordinates(intersectionPoint.z,intersectionPoint.y,glm::vec2(0.5f,0.25f));
    }
    // intersectionPoint is on top face
    else if (absY >= absX && absY >= absZ && intersectionPoint.y >= 0) {
        return calcTextureCoordinates(intersectionPoint.x,intersectionPoint.z,glm::vec2(0.25f,0.5f));
    }
    // intersectionPoint is on bottom face
    else if (absY >= absX && absY >= absZ && intersectionPoint.y < 0) {
        return calcTextureCoordinates(intersectionPoint.x,intersectionPoint.z,glm::vec2(0.25f,0.0f));
    }
    
}

// sCoord is the intersection point coordinate (can be x,y or z) that the value of s will map to
// tCoord is the intersection point coordinate (can be x,y or z) that the value of t will map to
// bottomLeftCoords is the bottom left coordinate of the box on the ppm image that the box face maps to
glm::vec2 Box::calcTextureCoordinates(float sCoord, float tCoord, glm::vec2 bottomLeftCoords) {
    float s = ((sCoord - (-0.5)) * 0.25) + bottomLeftCoords.x;
    float t = ((tCoord - (-0.5)) * 0.25) + bottomLeftCoords.y;
    return glm::vec2(s,t);
}