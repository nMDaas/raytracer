#include "ScaleTransform.h"

ParentSGNode* ScaleTransform::copyNode() {
    return new ScaleTransform(sx,sy,sz,name,scenegraph);
} 

ScaleTransform::ScaleTransform(float sx,float sy,float sz,const std::string& name,IScenegraph *graph) 
        :TransformNode(name,graph) {
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
    glm::mat4 transform = glm::scale(glm::mat4(1.0),glm::vec3(sx,sy,sz));
    setTransform(transform);
}

glm::vec3 ScaleTransform::getScale() {
    return glm::vec3(sx,sy,sz);
}

void ScaleTransform::accept(SGNodeVisitor* visitor) {
    return visitor->visitScaleTransform(this);
}