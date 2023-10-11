#ifndef _ROTATETRANSFORM_H_
#define _ROTATETRANSFORM_H_

#include "../IScenegraph.h"
#include "../SGNodeVisitor.h"

#include "TransformNode.h"
#include "ParentSGNode.h"

#include <glm/gtc/matrix_transform.hpp>

/* RotateTransform extends TransformNode */
class RotateTransform: public TransformNode {
    protected:
            float angleInRadians;
            glm::vec3 axis;
            ParentSGNode *copyNode();

    public:
        RotateTransform(float angleInRadians,float ax,float ay,float az,const std::string& name,IScenegraph *graph);

        glm::vec3 getRotationAxis();

        float getAngleInRadians();

        void accept(SGNodeVisitor* visitor);
};

#endif