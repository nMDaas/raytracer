#include "RaytracerRenderer.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

RaytracerRenderer::RaytracerRenderer(stack<glm::mat4>& mv, glm::vec4& in_s, glm::vec4& in_v)
: modelview(mv), s(in_s), v(in_v){}

RaytracerRenderer::~RaytracerRenderer(){}

/*
    to check for copy constructors
*/
RaytracerRenderer::RaytracerRenderer (RaytracerRenderer &t) {
    std::cout << "RAYTRACERRENDERER COPY CONSTRUCTOR CALLED" << std::endl;
}

void RaytracerRenderer::visitGroupNode(GroupNode *groupNode) {
    spdlog::debug("RaytracerRenderer - Group Node to draw: " +groupNode->getName());
    for (int i=0;i<groupNode->getChildren().size();i=i+1) {
        groupNode->getChildren()[i]->accept(this);
    }
}

void RaytracerRenderer::visitScaleTransform(ScaleTransform *scaleNode) {
    spdlog::debug("RaytracerRenderer - ScaleTransform Node to draw: " +scaleNode->getName());
    visitTransformNode(scaleNode);
}

void RaytracerRenderer::visitRotateTransform(RotateTransform *rotateNode) {
    spdlog::debug("RaytracerRenderer - RotateTransform Node to draw: " +rotateNode->getName());
    visitTransformNode(rotateNode);
}

void RaytracerRenderer::visitTranslateTransform(TranslateTransform *translateNode) {
    spdlog::debug("RaytracerRenderer - TranslateTransform Node to draw: " +translateNode->getName());
    visitTransformNode(translateNode);
}

void RaytracerRenderer::visitTransformNode(TransformNode *transformNode) {
    spdlog::debug("RaytracerRenderer - Transform Node to draw: " +transformNode->getName());
    modelview.push(modelview.top());
    spdlog::debug("modelview top: " + glm::to_string(modelview.top()));
    modelview.top() = modelview.top() * transformNode->getTransform();
    spdlog::debug("transform matrix: " + glm::to_string(transformNode->getTransform()));
    spdlog::debug("modelview top with transform: " + glm::to_string(modelview.top()));

    for (int i=0;i<transformNode->getChildren().size();i=i+1) {
        transformNode->getChildren()[i]->accept(this);
    }
    modelview.pop();
}

void RaytracerRenderer::visitLeafNode(LeafNode *leafNode) {
    spdlog::debug("RaytracerRenderer - Leaf Node to draw: " +leafNode->getName());

}

void RaytracerRenderer::visitLightNode(LightNode *lightNode) {
    spdlog::debug("RaytracerRenderer - Light Node to draw: " +lightNode->getName());
}

vector<util::Light> RaytracerRenderer::getLights(){}

void RaytracerRenderer::clearLights(){}

float RaytracerRenderer::getHitRecord() {
    std::cout << "minTIme: " << minTime << std::endl;
    return minTime;
}