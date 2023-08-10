#ifndef _RAYTRACERRENDERER_H_
#define _RAYTRACERRENDERER_H_
#include <stack>
#include <map>

#include <glm/gtx/string_cast.hpp>

#include "SGNodeVisitor.h"
#include "nodes/GroupNode.h"
#include "nodes/RotateTransform.h"
#include "nodes/ScaleTransform.h"
#include "nodes/TranslateTransform.h"
#include "nodes/TransformNode.h"
#include "nodes/LeafNode.h"
#include "nodes/LightNode.h"

/*
    RaytraceRenderer is a visitor that implements SGNodeVisitor and will be
    used to traverse the scenegraph and return a HitRecord */
class RaytracerRenderer: public SGNodeVisitor {
    public:

    RaytracerRenderer();
    ~RaytracerRenderer();

    /*
        to check for copy constructors
    */
    RaytracerRenderer (RaytracerRenderer &t);

    void visitGroupNode(GroupNode *groupNode);
    void visitScaleTransform(ScaleTransform *scaleNode);
    void visitRotateTransform(RotateTransform *rotateNode);
    void visitTranslateTransform(TranslateTransform *translateNode);
    void visitTransformNode(TransformNode *transformNode);
    void visitLeafNode(LeafNode *leafNode);
    void visitLightNode(LightNode *lightNode);
    vector<util::Light> getLights();
    void clearLights();

    private: 

};

#endif