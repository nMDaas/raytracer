#ifndef _TRANSFORMNODE_H_
#define _TRANSFORMNODE_H_

#include "../IScenegraph.h"
#include "ParentSGNode.h"

class TransformNode: public ParentSGNode {
    public:
      TransformNode(const std::string& name,IScenegraph *graph)
        :ParentSGNode(name,graph) {
      }
      
      ~TransformNode()	{

      }
};

#endif