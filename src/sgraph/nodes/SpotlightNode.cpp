#include "SpotlightNode.h"

/* SpotlightNode extends LightNode */
SpotlightNode::SpotlightNode(const std::string& name,IScenegraph *graph,glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,glm::vec4 direction,float spotAngle) 
:LightNode(name,graph,ambient,diffuse,specular) {
    light->setSpotDirection(direction.x,direction.y,direction.z);
    light->setSpotAngle(glm::radians(spotAngle));
}