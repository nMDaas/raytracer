#ifndef _SCALETRANSFORM_H_
#define _SCALETRANSFORM_H_

#include <glm/gtc/matrix_transform.hpp>

#include "../IScenegraph.h"
#include "../SGNodeVisitor.h"

#include "TransformNode.h"
#include "ParentSGNode.h"

class ScaleTransform : public TransformNode {
    protected:
        float sx,sy,sz;
        ParentSGNode *copyNode();

    public:
        ScaleTransform(float sx,float sy,float sz,const std::string& name,IScenegraph *graph);

        glm::vec3 getScale();

        void accept(SGNodeVisitor* visitor);
};

#endif