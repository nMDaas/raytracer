#include "RaytracerRenderer.h"

#include <fstream>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

RaytracerRenderer::RaytracerRenderer(stack<glm::mat4>& mv, glm::vec4& in_s, glm::vec4& in_v)
: AbstractRenderer(mv), s(in_s), v(in_v) {}

RaytracerRenderer::~RaytracerRenderer(){}

RaytracerRenderer::RaytracerRenderer (RaytracerRenderer &t) : AbstractRenderer(t.modelview), s(t.s), v(t.v) {
    std::cout << "RAYTRACER RENDERER COPY CONSTRUCTOR CALLED" << std::endl;
}

void RaytracerRenderer::visitLeafNode(LeafNode *leafNode) {
    spdlog::debug("RaytracerRenderer - Leaf Node to draw: " +leafNode->getName());

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
    else if (leafNode->getInstanceOf() == "cylinder") {
        hit = cylinder.calcTimes(_s,_v);
        if (hit) {
            newTime = cylinder.getTime();
        }
    }
    else if (leafNode->getInstanceOf() == "cone") {
        hit = cone.calcTimes(_s,_v);
        if (hit) {
            newTime = cone.getTime();
        }
    }
    else if (leafNode->getInstanceOf() == "triangle") {
        hit = triangle.calcTimes(_s,_v);
        if (hit) {
            newTime = triangle.getTime();
        }
    }

    if (hit) {
        if (newTime < hitRecordWithMinTime.t) {
            glm::vec4 intersectionPoint = getIntersection(newTime,_s,_v);
            //std::cout << "time: " << newTime << std::endl;
            glm::vec4 normal;
            normal = getNormal(intersectionPoint,leafNode->getInstanceOf());
            
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - intersectionPoint: " + glm::to_string(intersectionPoint));
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - normal: " + glm::to_string(normal));

            normal = glm::normalize(normal);
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - normal after normalizing: " + glm::to_string(normal));

            glm::vec2 textureCoordinates = getTextureCoordinates(intersectionPoint,leafNode->getInstanceOf());
        
            // points transformed to convert from object coordinate system to view coordinate system
            glm::mat4 mvt1 = modelview.top();
            intersectionPoint = mvt1 * intersectionPoint; 
            glm::mat4 mvt2 = modelview.top();
            normal = mvt2 * normal;
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - intersectionPoint x modelview top: " + glm::to_string(intersectionPoint));
            spdlog::debug("in RaytracerRenderer - visitLeafNode() - normal x modelview top: " + glm::to_string(normal));

            HitRecord newHitRecord = {newTime,intersectionPoint,normal,leafNode->getMaterial(),leafNode->getTexture(),textureCoordinates,leafNode->getName()};

            hitRecordWithMinTime = newHitRecord;
        }
    }

}

HitRecord& RaytracerRenderer::getHitRecord() {
    return hitRecordWithMinTime;
}

glm::vec4 RaytracerRenderer::getIntersection(float time, glm::vec4 _s, glm::vec4 _v){
    spdlog::debug("_s: " + glm::to_string(_s));
    spdlog::debug("_v: " + glm::to_string(_v));
    spdlog::debug("time: " + (int) time);
    spdlog::debug("getIntersection: " + glm::to_string(_s + (_v * time)));
    return _s + (_v * time);
}

glm::vec4 RaytracerRenderer::getNormal(glm::vec4 intersectionPoint,string instanceOf) {
    if (instanceOf == "box") {
        return box.getNormal(intersectionPoint);
    }
    else if (instanceOf == "sphere") {
        return sphere.getNormal(intersectionPoint);
    }
    else if (instanceOf == "cylinder") {
        return cylinder.getNormal(intersectionPoint);
    }
    else if (instanceOf == "cone") {
        return cone.getNormal(intersectionPoint);
    }
    else if (instanceOf == "triangle") {
        return triangle.getNormal(intersectionPoint);
    }
}

glm::vec2 RaytracerRenderer::getTextureCoordinates(glm::vec4 intersectionPoint, string instanceOf) {
    if (instanceOf == "sphere") {
        return sphere.getTextureCoordinates(intersectionPoint);
    }
    else if (instanceOf == "box") {
        return box.getTextureCoordinates(intersectionPoint);
    }
}