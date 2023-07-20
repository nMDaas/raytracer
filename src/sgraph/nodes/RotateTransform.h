#ifndef _ROTATETRANSFORM_H_
#define _ROTATETRANSFORM_H_

#include "../IScenegraph.h"
#include "TransformNode.h"

#include <glm/gtc/matrix_transform.hpp>

class RotateTransform: public TransformNode {
    protected:
            float angleInRadians;
            glm::vec3 axis;

            ParentSGNode *copyNode() {
                return new RotateTransform(angleInRadians,axis[0],axis[1],axis[2],name,scenegraph);
            }
    public:
        RotateTransform(float angleInRadians,float ax,float ay,float az,const std::string& name,IScenegraph *graph) 
                :TransformNode(name,graph) {
        }
};

#endif