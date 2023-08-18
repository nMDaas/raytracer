#include "GLScenegraphRenderer.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

GLScenegraphRenderer::GLScenegraphRenderer(stack<glm::mat4>& mv, map<string,util::ObjectInstance *>& os, util::ShaderLocationsVault& shaderLocs) 
    : modelview(mv), objects(os), shaderLocations(shaderLocs){
    //std::cout << "scenegraph constructor called" << std::endl;
}

GLScenegraphRenderer::~GLScenegraphRenderer() {}

/*
    to check for copy constructors
*/
GLScenegraphRenderer::GLScenegraphRenderer (GLScenegraphRenderer &t) : modelview(t.modelview) {
    std::cout << "GLScenegraphRenderer COPY CONSTRUCTOR CALLED" << std::endl;
}

void GLScenegraphRenderer::visitGroupNode(GroupNode *groupNode) {
    spdlog::debug("Group Node to draw: " +groupNode->getName());
    for (int i=0;i<groupNode->getChildren().size();i=i+1) {
        groupNode->getChildren()[i]->accept(this);
    }
}

void GLScenegraphRenderer::visitScaleTransform(ScaleTransform *scaleNode) {
    spdlog::debug("ScaleTransform Node to draw: " +scaleNode->getName());
    visitTransformNode(scaleNode);
}

void GLScenegraphRenderer::visitRotateTransform(RotateTransform *rotateNode) {
    spdlog::debug("RotateTransform Node to draw: " +rotateNode->getName());
    visitTransformNode(rotateNode);
}

void GLScenegraphRenderer::visitTranslateTransform(TranslateTransform *translateNode) {
    spdlog::debug("TranslateTransform Node to draw: " +translateNode->getName());
    visitTransformNode(translateNode);
}

void GLScenegraphRenderer::visitTransformNode(TransformNode *transformNode) {
    spdlog::debug("Transform Node to draw: " +transformNode->getName());
    modelview.push(modelview.top());
    modelview.top() = modelview.top() * transformNode->getTransform();
    for (int i=0;i<transformNode->getChildren().size();i=i+1) {
        transformNode->getChildren()[i]->accept(this);
    }
    modelview.pop();
}

void GLScenegraphRenderer::visitLeafNode(LeafNode *leafNode) {
    spdlog::debug("Leaf Node to draw: " +leafNode->getName());
     //send modelview matrix to GPU  
    glUniformMatrix4fv(shaderLocations.getLocation("modelview"), 1, GL_FALSE, glm::value_ptr(modelview.top()));
    glm::mat4 normalmatrix = glm::inverse(glm::transpose((modelview.top())));
    glUniformMatrix4fv(shaderLocations.getLocation("normalmatrix"), 1, false,glm::value_ptr(normalmatrix));
    util::Material mat = leafNode->getMaterial();
    glUniform3fv(shaderLocations.getLocation("material.ambient"), 1, glm::value_ptr(mat.getAmbient()));
    glUniform3fv(shaderLocations.getLocation("material.diffuse"), 1, glm::value_ptr(mat.getDiffuse()));
    glUniform3fv(shaderLocations.getLocation("material.specular"), 1,glm::value_ptr(mat.getSpecular()));
    glUniform1f(shaderLocations.getLocation("material.shininess"), mat.getShininess());

    objects[leafNode->getInstanceOf()]->draw();
}

void GLScenegraphRenderer::visitLightNode(LightNode *lightNode) {
    spdlog::debug("Light Node to draw: " +lightNode->getName());
    util::Light nodeLight = *lightNode->getLight();
    glm::vec4 pos = nodeLight.getPosition();
    nodeLight.setPosition(modelview.top() * pos);
    lights.push_back(nodeLight);
}

vector<util::Light> GLScenegraphRenderer::getLights() {
    return lights;
}

void GLScenegraphRenderer::clearLights() {
    lights.clear();
}

HitRecord GLScenegraphRenderer::getHitRecord() {}