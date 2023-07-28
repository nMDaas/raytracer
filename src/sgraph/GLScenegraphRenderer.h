#ifndef _GLSCENEGRAPHRENDERER_H_
#define _GLSCENEGRAPHRENDERER_H_

#include "SGNodeVisitor.h"
#include "nodes/GroupNode.h"

/*
    GLScenegraphRenderer is a visitor that implements SGNodeVisitor and will be
    used to traverse the scenegraph and render it */
class GLScenegraphRenderer: public SGNodeVisitor {
    public:
    GLScenegraphRenderer();

    ~GLScenegraphRenderer();

    /*
        to check for copy constructors
    */
    GLScenegraphRenderer (GLScenegraphRenderer &t);

    void visitGroupNode(GroupNode *groupNode);

};

#endif