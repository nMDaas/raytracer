#ifndef _ROTATETRANSFORM_H_
#define _ROTATETRANSFORM_H_

#include "../IScenegraph.h"
#include "TransformNode.h"

class RotateTransform: public TransformNode {
    public:
        RotateTransform(float angleInRadians,float ax,float ay,float az,const std::string& name,IScenegraph *graph) 
                :TransformNode(name,graph) {
        }
};

#endif