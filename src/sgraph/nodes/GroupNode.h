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

};
#endif