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
    //std::cout << "Modelviewtop: " << glm::to_string(modelview.top()) << std::endl;
    //std::cout << "Transform: " << glm::to_string(transformNode->getTransform()) << std::endl;
    //std::cout << "Modelviewtop: " << glm::to_string(modelview.top()) << std::endl;
    if (transformNode->getChildren().size()>0) {
        transformNode->getChildren()[0]->accept(this);
    }
    modelview.pop();
}

void GLScenegraphRenderer::visitLeafNode(LeafNode *leafNode) {
    //std::cout << "LeafNode to draw: " << leafNode->getName() << std::endl;
     //send modelview matrix to GPU  
    glUniformMatrix4fv(shaderLocations.getLocation("modelview"), 1, GL_FALSE, glm::value_ptr(modelview.top()));
    glm::mat4 normalmatrix = glm::inverse(glm::transpose((modelview.top())));
    glUniformMatrix4fv(shaderLocations.getLocation("normalmatrix"), 1, false,glm::value_ptr(normalmatrix));
    util::Material mat = leafNode->getMaterial();
    glUniform3fv(shaderLocations.getLocation("material.ambient"), 1, glm::value_ptr(mat.getAmbient()));
    //std::cout << "LeafNode diffuse: " << glm::to_string(mat.getDiffuse()) << std::endl;
    glUniform3fv(shaderLocations.getLocation("material.diffuse"), 1, glm::value_ptr(mat.getDiffuse()));
    glUniform3fv(shaderLocations.getLocation("material.specular"), 1,glm::value_ptr(mat.getSpecular()));
    glUniform1f(shaderLocations.getLocation("material.shininess"), mat.getShininess());

    objects[leafNode->getInstanceOf()]->draw();
}

void GLScenegraphRenderer::visitLightNode(LightNode *lightNode) {
    std::cout << "Light Node to draw: " << lightNode->getName() << std::endl;
    util::Light nodeLight = *lightNode->getLight();
    glm::vec4 pos = nodeLight.getPosition();
    nodeLight.setPosition(modelview.top() * pos);
    std::cout << "light pos: " << glm::to_string(pos) << std::endl;
    std::cout << "modelview.top: " << glm::to_string(modelview.top()) << std::endl;
    std::cout << "mult: " << glm::to_string( modelview.top() * pos) << std::endl;
    lights.push_back(nodeLight);
    lightCoordinateSystems.push_back("world");
}

vector<util::Light> GLScenegraphRenderer::getLights() {
    return lights;
}

void GLScenegraphRenderer::clearLights() {
    lights.clear();
}