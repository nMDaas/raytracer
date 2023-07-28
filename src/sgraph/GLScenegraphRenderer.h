#ifndef _GLSCENEGRAPHRENDERER_H_
#define _GLSCENEGRAPHRENDERER_H_
#include <stack>

#include "SGNodeVisitor.h"
#include "nodes/GroupNode.h"
#include "nodes/RotateTransform.h"
#include "nodes/ScaleTransform.h"
#include "nodes/TranslateTransform.h"
#include "nodes/TransformNode.h"
#include "nodes/LeafNode.h"

/*
    GLScenegraphRenderer is a visitor that implements SGNodeVisitor and will be
    used to traverse the scenegraph and render it */
class GLScenegraphRenderer: public SGNodeVisitor {
    public:
    GLScenegraphRenderer(stack<glm::mat4>& mv);

    ~GLScenegraphRenderer();

    /*
        to check for copy constructors
    */
    GLScenegraphRenderer (GLScenegraphRenderer &t);

    void visitGroupNode(GroupNode *groupNode);
    void visitScaleTransform(ScaleTransform *scaleNode);
    void visitRotateTransform(RotateTransform *rotateNode);
    void visitTranslateTransform(TranslateTransform *translateNode);
    void visitTransformNode(TransformNode *transformNode);
    void visitLeafNode(LeafNode *leafNode);

    private: 
    stack<glm::mat4>& modelview;

};

#endif