#ifndef _TRANSLATETRANSFORM_H_
#define _TRANSLATETRANSFORM_H_

#include "../IScenegraph.h"
#include "../SGNodeVisitor.h"

#include "TransformNode.h"
#include "ParentSGNode.h"

#include <glm/gtc/matrix_transform.hpp>

class TranslateTransform: public TransformNode {
    protected: 
    float tx, ty, tz;
    
    ParentSGNode *copyNode();
        
    public:
        TranslateTransform(float tx,float ty,float tz,const std::string& name,IScenegraph *graph);

        glm::vec3 getTranslate();

        void accept(SGNodeVisitor* visitor);
};

#endif