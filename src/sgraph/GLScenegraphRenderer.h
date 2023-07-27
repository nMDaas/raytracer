#ifndef _GLSCENEGRAPHRENDERER_H_
#define _GLSCENEGRAPHRENDERER_H_
#include <iostream>

#include "SGNodeVisitor.h"

/*
    GLScenegraphRenderer is a visitor that implements SGNodeVisitor and will be
    used to traverse the scenegraph and render it */
class GLScenegraphRenderer: public SGNodeVisitor {
    public:
    GLScenegraphRenderer() {
        std::cout << "scenegraph constructor called" << std::endl;
    }

    ~GLScenegraphRenderer() {}

    /*
        to check for copy constructors
    */
    GLScenegraphRenderer (GLScenegraphRenderer &t) {
        std::cout << "GLScenegraphRenderer COPY CONSTRUCTOR CALLED" << std::endl;
    }

    void visitGroupNode(GroupNode *groupNode) {
        std::cout << "In visitGroupNode() in GLScenegraphRender()" << std::endl;
    }

};

#endif