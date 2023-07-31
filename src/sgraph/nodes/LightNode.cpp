#include "LightNode.h"

LightNode::LightNode(const std::string& name,IScenegraph *graph,glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    :ChildSGNode(name,graph) {
    light = new util::Light();
    light->setAmbient(ambient.x,ambient.y,ambient.z);
    light->setDiffuse(diffuse.x,diffuse.y,diffuse.z);
    light->setSpecular(specular.x,specular.y,specular.z);
    
}

SGNode* LightNode::clone() {
    LightNode *newclone = new LightNode(name,scenegraph,light->getAmbient(),light->getDiffuse(),light->getSpecular());
    return newclone;
}

void LightNode::accept(SGNodeVisitor* visitor) {
    visitor->visitLightNode(this);
}

util::Light* LightNode::getLight() {
    return light;
}