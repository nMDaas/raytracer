#ifndef _TRANSFORMNODE_H_
#define _TRANSFORMNODE_H_

#include "../IScenegraph.h"
#include "../SGNodeVisitor.h"

#include "ParentSGNode.h"
#include "SGNode.h"

#include "glm/glm.hpp"

class TransformNode: public ParentSGNode {
    protected:
      glm::mat4 transform;
      
      void setTransform(glm::mat4& transform);

    public:
      TransformNode(const std::string& name,IScenegraph *graph);
      
      ~TransformNode();
      
      void accept(SGNodeVisitor* visitor);

      glm::mat4 getTransform();
};

#endif