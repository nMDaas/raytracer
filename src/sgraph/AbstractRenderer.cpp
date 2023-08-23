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
    spdlog::debug("Group Node: " +groupNode->getName());
    for (int i=0;i<groupNode->getChildren().size();i=i+1) {
        groupNode->getChildren()[i]->accept(this);
    }
}

void AbstractRenderer::visitScaleTransform(ScaleTransform *scaleNode) {
    spdlog::debug("ScaleTransform Node: " +scaleNode->getName());
    visitTransformNode(scaleNode);
}

void AbstractRenderer::visitRotateTransform(RotateTransform *rotateNode) {
    spdlog::debug("RotateTransform Node: " +rotateNode->getName());
    visitTransformNode(rotateNode);
}

void AbstractRenderer::visitTranslateTransform(TranslateTransform *translateNode) {
    spdlog::debug("TranslateTransform Node: " +translateNode->getName());
    visitTransformNode(translateNode);
}

void AbstractRenderer::visitTransformNode(TransformNode *transformNode) {
    spdlog::debug("Transform Node: " +transformNode->getName());
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

void AbstractRenderer::visitLightNode(LightNode *lightNode) {
    spdlog::debug("Light Node: " +lightNode->getName());
    util::Light nodeLight = *lightNode->getLight();
    glm::vec4 pos = nodeLight.getPosition();
    nodeLight.setPosition(modelview.top() * pos);
    lights.push_back(nodeLight);
}

vector<util::Light> AbstractRenderer::getLights() {
    spdlog::debug("getLights() called");
    return lights;
}

void AbstractRenderer::clearLights() {
    spdlog::debug("clearLights() called");
    lights.clear();
}