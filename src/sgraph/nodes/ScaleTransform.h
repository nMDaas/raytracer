#ifndef _SCALETRANSFORM_H_
#define _SCALETRANSFORM_H_

#include "../IScenegraph.h"
#include "TransformNode.h"

class ScaleTransform: public TransformNode {
    protected:
        float sx,sy,sz;

        ParentSGNode *copyNode() {
            return new ScaleTransform(sx,sy,sz,name,scenegraph);
        } 

    public:
        ScaleTransform(float sx,float sy,float sz,const std::string& name,IScenegraph *graph) 
                :TransformNode(name,graph) {
                this->sx = sx;
                this->sy = sy;
                this->sz = sz;
                glm::mat4 transform = glm::scale(glm::mat4(1.0),glm::vec3(sx,sy,sz));
                setTransform(transform);
        }

        glm::vec3 getScale() {
            return glm::vec3(sx,sy,sz);
        }
};

#endif