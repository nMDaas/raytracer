#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include <glm/glm.hpp>

class Cylinder {
    public:
        Cylinder();
        ~Cylinder();

        Cylinder (Cylinder &t); // to check for copy constructors
        bool calcTimes(glm::vec4 s, glm::vec4 v); // calculates tmin and tmax of a ray's intersection with a unit cylinder
        float getTime(); // returns the time of first intersection of the ray with the unit cylinder
        glm::vec4 getNormal(glm::vec4 intersectionPoint);

    private:
        glm::vec3 vmin = glm::vec3(-1.0f,0.0f,-1.0f); // minimum bounds of cylinder in Object Coordinate System
        glm::vec3 vmax = glm::vec3(1.0f,1.0f,1.0f); // maximum bounds of cylinder in Object Coordinate System
        float radius = 1.0f;
        float tmin;
        float tmax;
};

#endif