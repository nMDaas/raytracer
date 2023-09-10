#ifndef _SPOTLIGHTNODE_H_
#define _SPOTLIGHTNODE_H_

#include "LightNode.h"

class SpotlightNode: public LightNode {
    public: 
    SpotlightNode(const std::string& name,IScenegraph *graph,glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,glm::vec4 dir,float angle);
    private: 
    glm::vec4 direction;
    float spotAngle;
};

#endif