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

void TransformNode::addChild(SGNode *child) {
    this->children.push_back(child);
    child->setParent(this);
}

void TransformNode::setScenegraph(IScenegraph *graph) {
    AbstractSGNode::setScenegraph(graph);
    for (int i=0;i<children.size();i++)
    {
        children[i]->setScenegraph(graph);
    }
}

void TransformNode::accept(SGNodeVisitor* visitor) {
    std::cout << "In TransformNode" << std::endl; 
}

glm::mat4 TransformNode::getTransform() {
    return transform;
}