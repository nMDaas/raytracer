#ifndef __CONE_H__
#define __CONE_H__

#include <glm/glm.hpp>

class Cone {
    public:
        Cone();
        ~Cone();

        Cone (Cone &t); // to check for copy constructors
        bool calcTimes(glm::vec4 s, glm::vec4 v); // calculates tmin and tmax of a ray's intersection with a unit cone
        float getTime(); // returns the time of first intersection of the ray with the unit cone
        glm::vec4 getNormal(glm::vec4 intersectionPoint);

    private:
        glm::vec3 vmin = glm::vec3(-1.0f,0.0f,-1.0f); // minimum bounds of cone in Object Coordinate System
        glm::vec3 vmax = glm::vec3(1.0f,1.0f,1.0f); // maximum bounds of cone in Object Coordinate System
        float tmin;
        float tmax;
};

#endif