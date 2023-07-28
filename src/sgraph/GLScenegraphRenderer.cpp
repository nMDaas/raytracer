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
    std::cout << "GroupNode: " << groupNode->getName() << std::endl;
    for (int i=0;i<groupNode->getChildren().size();i=i+1) {
        groupNode->getChildren()[i]->accept(this);
    }
}

void GLScenegraphRenderer::visitScaleTransform(ScaleTransform *scaleNode) {
    std::cout << "ScaleTransform: " << scaleNode->getName() << std::endl;
    visitTransformNode(scaleNode);
}

void GLScenegraphRenderer::visitRotateTransform(RotateTransform *rotateNode) {
    std::cout << "RotateTransform: " << rotateNode->getName() << std::endl;
    visitTransformNode(rotateNode);
}

void GLScenegraphRenderer::visitTranslateTransform(TranslateTransform *translateNode) {
    std::cout << "TranslateTransform: " << translateNode->getName() << std::endl;
    visitTransformNode(translateNode);
}

void GLScenegraphRenderer::visitTransformNode(TransformNode *transformNode) {
    std::cout << "Transform: " << transformNode->getName() << std::endl;
    if (transformNode->getChildren().size()>0) {
        transformNode->getChildren()[0]->accept(this);
    }
}

void GLScenegraphRenderer::visitLeafNode(LeafNode *leafNode) {
    std::cout << "LeafNode to draw: " << leafNode->getName() << std::endl;
}