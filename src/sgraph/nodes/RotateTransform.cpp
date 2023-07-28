#include "RotateTransform.h"

ParentSGNode* RotateTransform::copyNode() {
        return new RotateTransform(angleInRadians,axis[0],axis[1],axis[2],name,scenegraph);
    }

RotateTransform::RotateTransform(float angleInRadians,float ax,float ay,float az,const std::string& name,IScenegraph *graph) 
        :TransformNode(name,graph) {
            this->angleInRadians = angleInRadians;
            this->axis = glm::vec3(ax,ay,az);
            glm::mat4 transform = glm::rotate(glm::mat4(1.0),this->angleInRadians,this->axis);
            setTransform(transform);
}

glm::vec3 RotateTransform::getRotationAxis() {
    return axis;
}

float RotateTransform::getAngleInRadians() {
    return angleInRadians;
}

void RotateTransform::accept(SGNodeVisitor* visitor) {
    return visitor->visitRotateTransform(this);
}