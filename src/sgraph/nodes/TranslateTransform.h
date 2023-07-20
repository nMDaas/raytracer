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
        }
};

#endif