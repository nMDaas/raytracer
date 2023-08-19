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
#include "../objects/Box.h"
#include "HitRecord.h"

/*
    RaytraceRenderer is a visitor that implements SGNodeVisitor and will be
    used to traverse the scenegraph and return a HitRecord */
class RaytracerRenderer: public SGNodeVisitor {
    public:

    RaytracerRenderer(stack<glm::mat4>& mv, glm::vec4& in_s, glm::vec4& in_v);
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

    HitRecord& getHitRecord();

    private: 
    stack<glm::mat4> modelview;
    glm::vec4 s;
    glm::vec4 v;
    Box box;
    float minTime = INFINITY;
    HitRecord hitRecordWithMinTime = {minTime,glm::vec4(0,0,0,0),glm::vec4(0,0,0,0),util::Material()};

    glm::vec4 getIntersection(float time);
    glm::vec4 getNormal(glm::vec4 intersectionPoint);

};

#endif