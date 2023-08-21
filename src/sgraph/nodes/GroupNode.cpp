#include <iostream>
#include <vector>

#include "GroupNode.h"

ParentSGNode* GroupNode::copyNode() {
    return new GroupNode(name,scenegraph);
}

GroupNode::GroupNode(const std::string& name,IScenegraph *graph)
      :ParentSGNode(name,graph) {      
}

GroupNode::~GroupNode() {}

void GroupNode::accept(SGNodeVisitor* visitor) {
    visitor->visitGroupNode(this);
}