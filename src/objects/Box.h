#ifndef __BOX_H__
#define __BOX_H__

#include <glm/glm.hpp>

class Box {
    public:
        Box();
        ~Box();

        Box (Box &t); // to check for copy constructors
        bool calcTime(glm::vec4 s, glm::vec4 v); 
        float getTime();

    private:
        glm::vec3 vmin = glm::vec3(-0.5f,-0.5f,-0.5f); // minimum bounds of box in Object Coordinate System
        glm::vec3 vmax = glm::vec3(0.5f,0.5f,0.5f); // maximum bounds of box in Object Coordinate System
        float tmin;
        float tmax;
};

#endif