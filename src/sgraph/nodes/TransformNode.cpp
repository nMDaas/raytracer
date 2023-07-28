#include "TransformNode.h"

void TransformNode::setTransform(glm::mat4& transform) {
    this->transform = transform;
}

TransformNode::TransformNode(const std::string& name,IScenegraph *graph)
:ParentSGNode(name,graph) {
    this->transform = glm::mat4(1.0);
}

TransformNode::~TransformNode()	{

}

// add another child to this node ONLY if this node doesn't already have a child
void TransformNode::addChild(SGNode *child) {
    if (this->children.size()>0)
    throw runtime_error("Transform node already has a child");
    this->children.push_back(child);
    child->setParent(this);
}

void TransformNode::setScenegraph(IScenegraph *graph) {
    AbstractSGNode::setScenegraph(graph);
    if (children.size()>0) {
        children[0]->setScenegraph(graph);
    }
}

void TransformNode::accept(SGNodeVisitor* visitor) {
    std::cout << "In TransformNode" << std::endl; 
}

glm::mat4 TransformNode::getTransform() {
    return transform;
}