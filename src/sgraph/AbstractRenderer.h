#ifndef _ABSTRACTRENDERER_H_
#define _ABSTRACTRENDERER_H_

#include "SGNodeVisitor.h"

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

/* RaytraceRenderer is an abstract class that implements SGNodeVisitor */
class AbstractRenderer : public SGNodeVisitor {

    protected: 
        stack<glm::mat4>& modelview;
        vector<util::Light> lights;

    public:
        AbstractRenderer(stack<glm::mat4>& mv);

        ~AbstractRenderer();

        // to check for copy constructors
        AbstractRenderer (AbstractRenderer &t);

        void visitGroupNode(GroupNode *groupNode);
        void visitScaleTransform(ScaleTransform *scaleNode);
        void visitRotateTransform(RotateTransform *rotateNode);
        void visitTranslateTransform(TranslateTransform *translateNode);
        void visitTransformNode(TransformNode *transformNode);
        void visitLightNode(LightNode *lightNode);
        vector<util::Light> getLights();
        void clearLights();

};

#endif