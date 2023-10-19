#include "Triangle.h"
#include <iostream>

#include <glm/gtx/string_cast.hpp>

Triangle::Triangle(){}

Triangle::Triangle(glm::vec4 v0_in, glm::vec4 v1_in, glm::vec4 v2_in) {
    v0 = v0_in; 
    v1 = v1_in;
    v2 = v2_in;
    e1 = v1 - v0;
    e2 = v2 - v0;
    float normalX = (e1.y * e2.z) - (e1.z * e2.y);
    float normalY = (e1.z * e2.x) - (e1.x * e2.z);
    float normalZ = (e1.x * e2.y) - (e1.y * e2.x);
    normal = normalize(glm::vec4(normalX,normalY,normalZ,0.0f));
}

Triangle::~Triangle(){}

// to check for copy constructors
/*
Triangle::Triangle (Triangle &t){
    v0 = t.v0; 
    v1 = t.v1;
    v2 = t.v2;
    e1 = t.e1;
    e2 = t.e2;
    normal = t.normal;
    std::cout << "TRIANGLE COPY CONSTRUCTOR CALLED" << std::endl;
}*/

bool Triangle::calcTimes(glm::vec4 s, glm::vec4 v) {
    std::cout << "in Triangle calcTimes()" << std::endl;
    std::cout << "v0: " << glm::to_string(v0) << std::endl;
    std::cout << "v1: " << glm::to_string(v1) << std::endl;
    std::cout << "v2: " << glm::to_string(v2) << std::endl;
    /*
    std::cout << "s: " << glm::to_string(s) << std::endl;
    std::cout << "v: " << glm::to_string(s) << std::endl;
    std::cout << "e1: " << glm::to_string(e1) << std::endl;
    std::cout << "e2: " << glm::to_string(e2) << std::endl;
    std::cout << "e1 * e2: " << glm::to_string(e1 * e2) << std::endl;
    std::cout << "noramalize(e1 * e2): " << glm::to_string(normalize(e1 * e2)) << std::endl;
    std::cout << "normal: " << glm::to_string(normal) << std::endl;*/
    float NDotRayDir = glm::dot(v,normal);
    if (NDotRayDir == 0) {
        std::cout << "normal and ray direction are perpedicular - no hit" << std::endl;
        // normal and ray direction are perpedicular, so ray direction is parallel to triangle so no intersection
        return false;
    }

    t = (-1.0f * (glm::dot(normal,s))) / glm::dot(normal,v); 

    glm::vec4 intersectionPoint = s + (v * t); 
    if (!pointInsideTriangle(intersectionPoint)) {
        std::cout << "point inside triangle - no hit" << std::endl;
        return false;
    }

    std::cout << "returning true - hit" << std::endl;
    return true;
}

float Triangle::getTime() {
    if (t > 0) {
        // triangle is in front of camera
        return t;
    }
    else {
        return INFINITY;
    }
    
}

glm::vec4 Triangle::getNormal(glm::vec4 intersectionPoint) {
    return normal;
}

glm::vec2 Triangle::getTextureCoordinates(glm::vec4 intersectionPoint) {
    return glm::vec2(0,0);
}

bool Triangle::pointInsideTriangle(glm::vec4 intersectionPoint) {
    glm::vec4 edge0 = v1 - v0;
    glm::vec4 edge1 = v2 - v1;
    glm::vec4 edge2 = v0 - v2;
    glm::vec4 C0 = intersectionPoint - v0;
    glm::vec4 C1 = intersectionPoint - v1;
    glm::vec4 C2 = intersectionPoint - v2;
    /*
    std::cout << "intersectionPoint: " << glm::to_string(intersectionPoint) << std::endl;
    std::cout << "v0: " << glm::to_string(v0) << std::endl;
    std::cout << "v1: " << glm::to_string(v1) << std::endl;
    std::cout << "v2: " << glm::to_string(v2) << std::endl;
    std::cout << "edge0: " << glm::to_string(edge0) << std::endl;
    std::cout << "edge1: " << glm::to_string(edge1) << std::endl;
    std::cout << "edge2: " << glm::to_string(edge2) << std::endl;
    std::cout << "C0: " << glm::to_string(C0) << std::endl;
    std::cout << "C1: " << glm::to_string(C1) << std::endl;
    std::cout << "C2: " << glm::to_string(C2) << std::endl;
    std::cout << "edge0 * C0: " << glm::to_string(getCrossProduct(edge0,C0)) << std::endl;
    std::cout << "edge1 * C1: " << glm::to_string(getCrossProduct(edge1,C1)) << std::endl;
    std::cout << "edge2 * C2: " << glm::to_string(getCrossProduct(edge2,C2)) << std::endl;
    std::cout << "glm::dot(normal, edge0 * C0): " << glm::dot(normal, getCrossProduct(edge0,C0)) << std::endl;
    std::cout << "glm::dot(normal, edge1 * C1): " << glm::dot(normal, getCrossProduct(edge1,C1)) << std::endl;
    std::cout << "glm::dot(normal, edge2 * C2): " << glm::dot(normal, getCrossProduct(edge2,C2)) << std::endl;
    */
    if ((glm::dot(normal, getCrossProduct(edge0,C0)) >= 0) && 
    (glm::dot(normal, getCrossProduct(edge1,C1)) >= 0) &&
    (glm::dot(normal, getCrossProduct(edge2,C2)) >= 0)) {
        std::cout << "point inside triangle" << std::endl;
        return true;
    }
    else {
        std::cout << "point outside triangle" << std::endl;
        return false;
    }

}

glm::vec4 Triangle::getCrossProduct(glm::vec4 vec1, glm::vec4 vec2) {
    float crossX = (vec1.y * vec2.z) - (vec1.z * vec2.y);
    float crossY = (vec1.z * vec2.x) - (vec1.x * vec2.z);
    float crossZ = (vec1.x * vec2.y) - (vec1.y * vec2.x);
    return glm::vec4(crossX,crossY,crossZ,0);
}

void Triangle::printTriangleDetails() {
    std::cout << "---Triangle---" << std::endl;
    std::cout << "v0: " << glm::to_string(v0) << std::endl;
    std::cout << "v1: " << glm::to_string(v1) << std::endl;
    std::cout << "v2: " << glm::to_string(v2) << std::endl;
    std::cout << "normal: " << glm::to_string(normal) << std::endl;
}