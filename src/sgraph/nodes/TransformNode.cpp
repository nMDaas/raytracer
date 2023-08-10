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

glm::mat4 TransformNode::getTransform() {
    return transform;
}