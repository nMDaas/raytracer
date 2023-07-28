#include "GLScenegraphRenderer.h"

#include <iostream>

GLScenegraphRenderer::GLScenegraphRenderer() {
    std::cout << "scenegraph constructor called" << std::endl;
}

GLScenegraphRenderer::~GLScenegraphRenderer() {}

/*
    to check for copy constructors
*/
GLScenegraphRenderer::GLScenegraphRenderer (GLScenegraphRenderer &t) {
    std::cout << "GLScenegraphRenderer COPY CONSTRUCTOR CALLED" << std::endl;
}

void GLScenegraphRenderer::visitGroupNode(GroupNode *groupNode) {
    std::cout << "In visitGroupNode() in GLScenegraphRender(): " << groupNode->getName() <<  std::endl;
}