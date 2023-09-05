#include "Cone.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

Cone::Cone(){}

Cone::~Cone(){}

// to check for copy constructors
Cone::Cone (Cone &t){
    std::cout << "CONE COPY CONSTRUCTOR CALLED" << std::endl;
}

// calculates tmin and tmax of a ray's intersection with a unit box
bool Cone::calcTimes(glm::vec4 s, glm::vec4 v) {
    spdlog::debug("In Cone::calcTimes()");
    spdlog::debug("s: " + glm::to_string(s));
    spdlog::debug("v: " + glm::to_string(v));

    float a = pow(v.z,2) + pow(v.x,2) - pow(v.y,2);
    float b = (2 * v.z * s.z) + (2 * v.x * s.x) + (-2 * v.y * s.y) + (2 * v.y);
    float c = pow(s.z,2) + pow(s.x,2) - pow(s.y,2) + (2 * s.y) - 1.0f;

    spdlog::debug("a: " + (int) a); 
    spdlog::debug("b: " + (int) b); 
    spdlog::debug("c: " + (int) c); 

    float discriminant = pow(b,2) - (4 * a * c);
    spdlog::debug("discriminant: " + (int) discriminant);
    if (discriminant < 0) {
        return false;
    }

    tmin = (-b + sqrt(discriminant)) / (2 * a);
    tmax = (-b - sqrt(discriminant)) / (2 * a);

    spdlog::debug("tmin: " + (int) tmin);
    spdlog::debug("tmax: " + (int) tmax);

    float tMinY = s.y + (tmin * v.y);
    float tMaxY = s.y + (tmax * v.y);
    spdlog::debug("tMinY: " + (int) tMinY);
    spdlog::debug("tMaxY: " + (int) tMaxY);

    if (tMinY < 0 || tMinY > 1) { 
        tmin = INFINITY;
    }

    if (tMaxY < 0 || tMaxY > 1) { 
        tmax = INFINITY;
    }

    if (tmin > tmax) {
        std::swap(tmin,tmax);
    }

    return true;
}

// returns the time of first intersection of the ray with the unit cone
float Cone::getTime() {
    spdlog::debug("In Cone::getTime()");

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

glm::vec4 Cone::getNormal(glm::vec4 intersectionPoint) {
    spdlog::debug("In Cone::getNormal()");
    glm::vec4 normal(0,0,0,0);

    bool onCylinderEdge;

    if ((intersectionPoint.y > 0.999f) && (intersectionPoint.y < 1.001f)) {
        spdlog::debug("at ymax");
        normal.y = 1;
        onCylinderEdge = true;
    }
    else if ((intersectionPoint.y > -0.001f) && (intersectionPoint.y < 0.001)) {
        spdlog::debug("at ymin");
        normal.y = -1;
        onCylinderEdge = true;
    }
    else {
        spdlog::debug("between ymin and ymax");
        normal.y = 0.0f;
        onCylinderEdge = false;
    }

    if (onCylinderEdge) {
        if ((intersectionPoint.x < 1.001f ) && (intersectionPoint.x > 0.999f)) {
            normal.x = 1;
        }
        else if ((intersectionPoint.x > -1.001f) && (intersectionPoint.x < -0.999f)) {
            normal.x = -1;
        }
        else {
            normal.x = 0;
        }

        if ((intersectionPoint.z < 1.001f ) && (intersectionPoint.z > 0.999f)) {
            normal.z = 1;
        }
        else if ((intersectionPoint.z > -1.001f) && (intersectionPoint.z < -0.999f)) {
            normal.z = -1;
        }
        else {
            normal.z = 0;
        }
    }
    else {
        normal.x = intersectionPoint.x;
        normal.z = intersectionPoint.z;
    }

    spdlog::debug("interesectionPoint: " + glm::to_string(intersectionPoint));
    spdlog::debug("normal: " + glm::to_string(normal));

    return normal;
}