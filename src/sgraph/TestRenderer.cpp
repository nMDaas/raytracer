#include "TestRenderer.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

TestRenderer::TestRenderer(stack<glm::mat4>& mv, glm::vec4& in_s, glm::vec4& in_v) 
: AbstractRenderer(mv), s(in_s), v(in_v) {}

TestRenderer::~TestRenderer() {

}

// to check for copy constructors
TestRenderer::TestRenderer (TestRenderer &t) : AbstractRenderer(t.modelview), s(t.s), v(t.v) {
    std::cout << "TestRenderer COPY CONSTRUCTOR CALLED" << std::endl;
}

void TestRenderer::visitLeafNode(LeafNode *leafNode) {
    spdlog::info("visitLeafNode(): " +leafNode->getName());

    // inverse of modelview.top() are the transforms to convert back to Object Coordinate System
    glm::mat4 inverseTransform = glm::inverse(modelview.top()); 
    spdlog::debug("modelview top: " + glm::to_string(modelview.top()));
    spdlog::debug("inverseTransform: " + glm::to_string(inverseTransform));
    glm::vec4 _s = inverseTransform * s; // s transformed to Object Coordinate System
    glm::vec4 _v = inverseTransform * v; // s transformed to Object Coordinate System
    spdlog::debug("inverseS: " + glm::to_string(_s));
    spdlog::debug("inverseV: " + glm::to_string(_v));

    bool hit; // did the ray hit the leaf
    float newTime;
    if (leafNode->getInstanceOf() == "box") {
        hit = box.calcTimes(_s,_v);
        if (hit) {
            newTime = box.getTime();
        }
    }
    else if (leafNode->getInstanceOf() == "sphere") {
        hit = sphere.calcTimes(_s,_v);
        if (hit) {
            newTime = sphere.getTime();
        }
    }

    if (hit) {
        if (newTime < hitRecordWithMinTime.t) {
            glm::vec4 intersectionPoint = getIntersection(newTime,_s,_v);
            glm::vec4 normal;
            if (leafNode->getInstanceOf() == "box") {
                normal = getNormal(intersectionPoint,"box");
            }
            else if (leafNode->getInstanceOf() == "sphere") {
                normal = getNormal(intersectionPoint,"sphere");
            }
            
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - intersectionPoint: " + glm::to_string(intersectionPoint));
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - normal: " + glm::to_string(normal));

            normal = glm::normalize(normal);
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - normal after normalizing: " + glm::to_string(normal));
        
            // points transformed to convert from object coordinate system to view coordinate system
            intersectionPoint = modelview.top() * intersectionPoint; 
            normal = modelview.top() * normal;
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - intersectionPoint x modelview top: " + glm::to_string(intersectionPoint));
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - normal x modelview top: " + glm::to_string(normal));

            HitRecord newHitRecord = {newTime,intersectionPoint,normal,leafNode->getMaterial()};

            hitRecordWithMinTime = newHitRecord;
        }
    }
}

HitRecord& TestRenderer::getHitRecord() {
    return hitRecordWithMinTime;
}

glm::vec4 TestRenderer::getIntersection(float time, glm::vec4 _s, glm::vec4 _v){
    spdlog::debug("_s: " + glm::to_string(_s));
    spdlog::debug("_v: " + glm::to_string(_v));
    spdlog::debug("time: " + (int) time);
    spdlog::debug("getIntersection: " + glm::to_string(_s + (_v * time)));
    return _s + (_v * time);
}

glm::vec4 TestRenderer::getNormal(glm::vec4 intersectionPoint,string instanceOf) {
    if (instanceOf == "box") {
        return box.getNormal(intersectionPoint);
    }
    else if (instanceOf == "sphere") {
        return sphere.getNormal(intersectionPoint);
    }
}