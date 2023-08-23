#include "GLScenegraphRenderer.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

GLScenegraphRenderer::GLScenegraphRenderer(stack<glm::mat4>& mv, map<string,util::ObjectInstance *>& os, util::ShaderLocationsVault& shaderLocs) 
    : AbstractRenderer(mv), objects(os), shaderLocations(shaderLocs){
}

GLScenegraphRenderer::~GLScenegraphRenderer() {}

GLScenegraphRenderer::GLScenegraphRenderer (GLScenegraphRenderer &t) : AbstractRenderer(t.modelview), objects(t.objects), shaderLocations(t.shaderLocations) {
    std::cout << "GLScenegraphRenderer COPY CONSTRUCTOR CALLED" << std::endl;
}

void GLScenegraphRenderer::visitLeafNode(LeafNode *leafNode) {
    spdlog::debug("Leaf Node to draw: " +leafNode->getName());
     //send modelview matrix to GPU  
    glUniformMatrix4fv(shaderLocations.getLocation("modelview"), 1, GL_FALSE, glm::value_ptr(modelview.top()));
    glm::mat4 normalmatrix = glm::inverse(glm::transpose((modelview.top())));
    glUniformMatrix4fv(shaderLocations.getLocation("normalmatrix"), 1, false,glm::value_ptr(normalmatrix));
    util::Material* mat = leafNode->getMaterial();
    glUniform3fv(shaderLocations.getLocation("material.ambient"), 1, glm::value_ptr(mat->getAmbient()));
    glUniform3fv(shaderLocations.getLocation("material.diffuse"), 1, glm::value_ptr(mat->getDiffuse()));
    glUniform3fv(shaderLocations.getLocation("material.specular"), 1,glm::value_ptr(mat->getSpecular()));
    glUniform1f(shaderLocations.getLocation("material.shininess"), mat->getShininess());

    objects[leafNode->getInstanceOf()]->draw();
}