#include "SpotlightNode.h"

SpotlightNode::SpotlightNode(const std::string& name,IScenegraph *graph,glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,glm::vec4 dir,float angle) 
:LightNode(name,graph,ambient,diffuse,specular), direction(dir), spotAngle(angle) {}
