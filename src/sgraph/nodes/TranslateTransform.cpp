#include "TranslateTransform.h"

ParentSGNode* TranslateTransform::copyNode() {
    return new TranslateTransform(tx,ty,tz,name,scenegraph);
}

TranslateTransform::TranslateTransform(float tx,float ty,float tz,const std::string& name,IScenegraph *graph) 
    :TransformNode(name,graph) {
        this->tx = tx;
        this->ty = ty;
        this->tz = tz;
        glm::mat4 transform = glm::translate(glm::mat4(1.0),glm::vec3(tx,ty,tz));
        setTransform(transform);
}

glm::vec3 TranslateTransform::getTranslate() {
    return glm::vec3(tx,ty,tz);
}

void TranslateTransform::accept(SGNodeVisitor* visitor) {
    std::cout << "In TranslateTransform" << std::endl; 
}