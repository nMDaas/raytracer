#ifndef _TRANSFORMNODE_H_
#define _TRANSFORMNODE_H_

#include "../IScenegraph.h"
#include "../SGNodeVisitor.h"

#include "ParentSGNode.h"
#include "SGNode.h"

#include "glm/glm.hpp"

/* TransformNode extends ParentSGNode */
class TransformNode: public ParentSGNode {
    protected:
      glm::mat4 transform;
      
      void setTransform(glm::mat4& transform);

    public:
      TransformNode(const std::string& name,IScenegraph *graph);
      
      ~TransformNode();
      
      virtual void accept(SGNodeVisitor* visitor)=0;

      glm::mat4 getTransform();
};

#endif