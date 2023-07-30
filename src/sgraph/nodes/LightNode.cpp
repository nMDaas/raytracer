#include "LightNode.h"

LightNode::LightNode(const std::string& name,IScenegraph *graph)
    :ChildSGNode(name,graph) {}

SGNode* LightNode::clone() {
    LightNode *newclone = new LightNode(name,scenegraph);
    return newclone;
}

void LightNode::accept(SGNodeVisitor* visitor) {
    //visitor->visitLightNode(this);
}