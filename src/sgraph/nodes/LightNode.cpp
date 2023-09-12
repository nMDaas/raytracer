#include "LightNode.h"

LightNode::LightNode(const std::string& name,IScenegraph *graph,glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    :ChildSGNode(name,graph) {
    light = new util::Light();
    light->setPosition(0.0f,0.0f,0.0f);
    light->setAmbient(ambient.x,ambient.y,ambient.z);
    light->setDiffuse(diffuse.x,diffuse.y,diffuse.z);
    light->setSpecular(specular.x,specular.y,specular.z);
    generateLightCells(ambient,diffuse,specular);
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

void LightNode::generateLightCells(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    lightCells.push_back(*light); //main light at bottom left corner (x,y,z)
    util::Light light2; //light above (x,y+1,z)
    light2.setPosition(0.0f,1.0f,0.0f);
    light2.setAmbient(ambient.x,ambient.y,ambient.z);
    light2.setDiffuse(diffuse.x,diffuse.y,diffuse.z);
    light2.setSpecular(specular.x,specular.y,specular.z);
    util::Light light3; //light across (x+1,y+1,z)
    light3.setPosition(1.0f,1.0f,0.0f);
    light3.setAmbient(ambient.x,ambient.y,ambient.z);
    light3.setDiffuse(diffuse.x,diffuse.y,diffuse.z);
    light3.setSpecular(specular.x,specular.y,specular.z);
    util::Light light4; //light on right (x+1,y,z)
    light4.setPosition(1.0f,0.0f,0.0f);
    light4.setAmbient(ambient.x,ambient.y,ambient.z);
    light4.setDiffuse(diffuse.x,diffuse.y,diffuse.z);
    light4.setSpecular(specular.x,specular.y,specular.z);
    lightCells.push_back(light2);
    lightCells.push_back(light3);
    lightCells.push_back(light4);
}

std::vector<util::Light>* LightNode::getLightCells() {
    return &lightCells;
}