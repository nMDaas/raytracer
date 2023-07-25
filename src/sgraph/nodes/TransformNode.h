#ifndef _TRANSFORMNODE_H_
#define _TRANSFORMNODE_H_

#include "../IScenegraph.h"
#include "ParentSGNode.h"

#include "glm/glm.hpp"

class TransformNode: public ParentSGNode {
    protected:
      glm::mat4 transform;
      
      void setTransform(glm::mat4& transform) {
        this->transform = transform;
      }

    public:
      TransformNode(const std::string& name,IScenegraph *graph)
        :ParentSGNode(name,graph) {
        this->transform = glm::mat4(1.0);
      }
      
      ~TransformNode()	{

      }

      // add another child to this node ONLY if this node doesn't already have a child
    void addChild(SGNode *child) {
      if (this->children.size()>0)
        throw runtime_error("Transform node already has a child");
      this->children.push_back(child);
      child->setParent(this);
    }

    void setScenegraph(IScenegraph *graph) {
      AbstractSGNode::setScenegraph(graph);
      if (children.size()>0) {
          children[0]->setScenegraph(graph);
      }
    }
};

#endif