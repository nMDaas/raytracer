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

SGNode* GroupNode::clone() {
    std::vector<SGNode *> newc;

    for (int i=0;i<children.size();i++) {
        newc.push_back(children[i]->clone());
    }

    GroupNode *newgroup = new GroupNode(name,scenegraph);

    for (int i=0;i<children.size();i++) {
        try
        {
        newgroup->addChild(newc[i]);
        }
        catch (std::runtime_error e)
        {

        }
    }
    return newgroup;
}

void GroupNode::setScenegraph(IScenegraph *graph) {
    AbstractSGNode::setScenegraph(graph);
    for (int i=0;i<children.size();i++)
    {
        children[i]->setScenegraph(graph);
    }
}

void GroupNode::accept(SGNodeVisitor* visitor) {
    visitor->visitGroupNode(this);
}