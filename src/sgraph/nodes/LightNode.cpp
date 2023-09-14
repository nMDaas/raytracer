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

    lightCells.push_back(light);

    for (int lw = 0; lw < lightWidth; lw ++) {
        for (int lh = 0; lh < lightHeight; lh ++) {
            if (!(lw == 0 && lh == 0)) {
                glm::vec3 pos = glm::vec3(lw * cellSize, lh * cellSize, 0.0f);
                util::Light* newLight = new util::Light(); //light above (x,y+1,z)
                newLight->setPosition(lw * cellSize, lh * cellSize, 1.0f);
                newLight->setAmbient(ambient.x,ambient.y,ambient.z);
                newLight->setDiffuse(diffuse.x,diffuse.y,diffuse.z);
                newLight->setSpecular(specular.x,specular.y,specular.z);
                lightCells.push_back(newLight);
            }
        }
    }
}

std::vector<util::Light*>* LightNode::getLightCells() {
    return &lightCells;
}