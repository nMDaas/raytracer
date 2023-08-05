#include "GLScenegraphRenderer.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

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
    //std::cout << "GroupNode: " << groupNode->getName() << std::endl;
    for (int i=0;i<groupNode->getChildren().size();i=i+1) {
        //std::cout << "new child: " << groupNode->getChildren()[i]->getName() << std::endl;
        groupNode->getChildren()[i]->accept(this);
    }
    //std::cout << "exiting group node: " << groupNode->getName() << std::endl;
}

void GLScenegraphRenderer::visitScaleTransform(ScaleTransform *scaleNode) {
    //std::cout << "ScaleTransform: " << scaleNode->getName() << std::endl;
    visitTransformNode(scaleNode);
}

void GLScenegraphRenderer::visitRotateTransform(RotateTransform *rotateNode) {
    //std::cout << "RotateTransform: " << rotateNode->getName() << std::endl;
    visitTransformNode(rotateNode);
}

void GLScenegraphRenderer::visitTranslateTransform(TranslateTransform *translateNode) {
    //std::cout << "TranslateTransform: " << translateNode->getName() << std::endl;
    visitTransformNode(translateNode);
}

void GLScenegraphRenderer::visitTransformNode(TransformNode *transformNode) {
    //std::cout << "Transform: " << transformNode->getName() << std::endl;
    modelview.push(modelview.top());
    modelview.top() = modelview.top() * transformNode->getTransform();
    if (transformNode->getChildren().size()>0) {
        transformNode->getChildren()[0]->accept(this);
    }
    modelview.pop();
}

void GLScenegraphRenderer::visitLeafNode(LeafNode *leafNode) {
    //std::cout << "LeafNode to draw: " << leafNode->getName() << std::endl;
     //send modelview matrix to GPU  
    glUniformMatrix4fv(shaderLocations.getLocation("modelview"), 1, GL_FALSE, glm::value_ptr(modelview.top()));
    glUniform4fv(shaderLocations.getLocation("vColor"),1,glm::value_ptr(leafNode->getMaterial().getAmbient()));
    objects[leafNode->getInstanceOf()]->draw();
}

void GLScenegraphRenderer::visitLightNode(LightNode *lightNode) {
    //std::cout << "Light Node to draw: " << lightNode->getName() << std::endl;
    util::Light nodeLight = *lightNode->getLight();
    lights.push_back(nodeLight);
    lightCoordinateSystems.push_back("world");
}

vector<util::Light> GLScenegraphRenderer::getLights() {
    return lights;
}

void GLScenegraphRenderer::clearLights() {
    lights.clear();
}