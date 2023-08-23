#include "AbstractRenderer.h"
#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

AbstractRenderer::AbstractRenderer(stack<glm::mat4>& mv) : modelview(mv){
}

AbstractRenderer::~AbstractRenderer(){}

// to check for copy constructors
AbstractRenderer::AbstractRenderer (AbstractRenderer &t) : modelview(t.modelview) {
    std::cout << "AbstractRenderer COPY CONSTRUCTOR CALLED" << std::endl;
}

void AbstractRenderer::visitGroupNode(GroupNode *groupNode) {
    spdlog::info("Group Node to draw: " +groupNode->getName());
    for (int i=0;i<groupNode->getChildren().size();i=i+1) {
        groupNode->getChildren()[i]->accept(this);
    }
}

void AbstractRenderer::visitScaleTransform(ScaleTransform *scaleNode) {
    spdlog::info("ScaleTransform Node to draw: " +scaleNode->getName());
    visitTransformNode(scaleNode);
}

void AbstractRenderer::visitRotateTransform(RotateTransform *rotateNode) {
    spdlog::info("RotateTransform Node to draw: " +rotateNode->getName());
    visitTransformNode(rotateNode);
}

void AbstractRenderer::visitTranslateTransform(TranslateTransform *translateNode) {
    spdlog::info("TranslateTransform Node to draw: " +translateNode->getName());
    visitTransformNode(translateNode);
}

void AbstractRenderer::visitTransformNode(TransformNode *transformNode) {
    spdlog::info("Transform Node to draw: " +transformNode->getName());
    modelview.push(modelview.top());
    modelview.top() = modelview.top() * transformNode->getTransform();
    for (int i=0;i<transformNode->getChildren().size();i=i+1) {
        transformNode->getChildren()[i]->accept(this);
    }
    modelview.pop();
}

void AbstractRenderer::visitLightNode(LightNode *lightNode) {
    spdlog::info("Light Node to draw: " +lightNode->getName());
    util::Light nodeLight = *lightNode->getLight();
    glm::vec4 pos = nodeLight.getPosition();
    nodeLight.setPosition(modelview.top() * pos);
    lights.push_back(nodeLight);
}

vector<util::Light> AbstractRenderer::getLights() {
    spdlog::info("getLights() method");
    return lights;
}

void AbstractRenderer::clearLights() {
    spdlog::info("clearLights()");
    lights.clear();
}

HitRecord& AbstractRenderer::getHitRecord() {
    spdlog::info("getHitRecord() method");
}