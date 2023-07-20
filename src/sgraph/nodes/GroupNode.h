#ifndef _GROUPNODE_H_
#define _GROUPNODE_H_
#include <iostream>

#include "../IScenegraph.h"
#include "ParentSGNode.h"

class GroupNode : public ParentSGNode {
    public:
    GroupNode(const std::string& name,IScenegraph *graph)
      :ParentSGNode(name,graph) {      
    }
	
    ~GroupNode() {
      
    }

    // add another child to this node
    void addChild(SGNode *child) {
      children.push_back(child);
      child->setParent(this);
    }

};
#endif