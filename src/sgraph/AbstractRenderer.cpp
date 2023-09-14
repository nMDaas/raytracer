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

// for each light node, a vector<util::Light> is added to lightCellConnections
// if the light is a point light, this vector only contains one light (size = 1)
// if the light is an area light, this vector will have more lights (size > 1)
void AbstractRenderer::visitLightNode(LightNode *lightNode) {
    spdlog::debug("Light Node: " +lightNode->getName());
    std::vector<util::Light*>* nodeLightCellsP = lightNode->getLightCells();
    std::vector<util::Light*> nodeLightCells = *nodeLightCellsP;
    std::vector<util::Light> newLightCollection;
    for (int i=0; i < nodeLightCellsP->size(); i++) {
        util::Light nodeLight = *nodeLightCells[i];
        glm::vec4 pos = nodeLight.getPosition();
        nodeLight.setPosition(modelview.top() * pos);
        spdlog::debug("light: " + i);
        spdlog::debug ("position: " + glm::to_string(modelview.top() * pos));
        if (i == 0) {
            lights.push_back(nodeLight);
        }
        newLightCollection.push_back(nodeLight);
    }
    lightCollections.push_back(newLightCollection);
}

vector<util::Light> AbstractRenderer::getLights() {
    spdlog::debug("getLights() called");
    return lights;
}

void AbstractRenderer::clearLights() {
    spdlog::debug("clearLights() called");
    lights.clear();
}

vector<vector<util::Light>> AbstractRenderer::getLightCollections() {
    return lightCollections;
}

void AbstractRenderer::clearLightCollections() {
    lightCollections.clear();
}