#ifndef _LIGHTNODE_H_
#define _LIGHTNODE_H_

#include "Light.h"

#include "ChildSGNode.h"
#include "../IScenegraph.h"
#include "SGNode.h"

/* LightNode extends ChildSGNode */
class LightNode: public ChildSGNode {
    protected: 
    util::Light* light;
    std::vector<util::Light*> lightCells;

    public: 
    LightNode(const std::string& name,IScenegraph *graph,glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    SGNode *clone();
    void accept(SGNodeVisitor* visitor);
    util::Light* getLight();
    std::vector<util::Light*>* getLightCells();

    private:
    void generateLightCells(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular); 

    // each cell is described as (lightWidth,lightHeight)
    int lightWidth = 8; 
    int lightHeight = 8; 
    float cellSize = 15.0f; // width and height difference bewtween each cell
};

#endif