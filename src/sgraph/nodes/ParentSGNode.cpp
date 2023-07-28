#include "ParentSGNode.h"

#include <iostream>

ParentSGNode::ParentSGNode(const std::string& name,IScenegraph *scenegraph)
: AbstractSGNode(name,scenegraph) {}

ParentSGNode::~ParentSGNode() {
    for (int i=0;i<children.size();i++) {
        delete children[i];
    }
}

SGNode* ParentSGNode::clone() {
    ParentSGNode * newtransform = copyNode();

    for (int i=0;i<children.size();i=i+1) {
            newtransform->addChild(children[i]->clone());
    }

    return newtransform;
}

vector<SGNode *> ParentSGNode::getChildren() {
    return children;
}