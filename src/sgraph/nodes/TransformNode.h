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

      // add another child to this node ONLY if this node doesn't already have a child
      void addChild(SGNode *child);

      void setScenegraph(IScenegraph *graph);
      
      void accept(SGNodeVisitor* visitor);

      glm::mat4 getTransform();
};

#endif