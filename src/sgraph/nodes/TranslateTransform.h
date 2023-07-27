#ifndef _TRANSLATETRANSFORM_H_
#define _TRANSLATETRANSFORM_H_

#include "../IScenegraph.h"
#include "TransformNode.h"

class TranslateTransform: public TransformNode {
    protected: 
    float tx, ty, tz;
    
    ParentSGNode *copyNode() {
            return new TranslateTransform(tx,ty,tz,name,scenegraph);
        }
        
    public:
        TranslateTransform(float tx,float ty,float tz,const std::string& name,IScenegraph *graph) 
                :TransformNode(name,graph) {
                    this->tx = tx;
                    this->ty = ty;
                    this->tz = tz;
                    glm::mat4 transform = glm::translate(glm::mat4(1.0),glm::vec3(tx,ty,tz));
                    setTransform(transform);
        }

        glm::vec3 getTranslate() {
            return glm::vec3(tx,ty,tz);
        }

        void accept(SGNodeVisitor* visitor) {
            
        }
};

#endif