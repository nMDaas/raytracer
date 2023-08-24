#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include <glm/glm.hpp>

class Cylinder {
    public:
        Cylinder();
        ~Cylinder();

        Cylinder (Cylinder &t); // to check for copy constructors
        bool calcTimes(glm::vec4 s, glm::vec4 v); // calculates tmin and tmax of a ray's intersection with a unit box
        float getTime(); // returns the time of first intersection of the ray with the unit box
        glm::vec4 getNormal(glm::vec4 intersectionPoint);

    private:
        float tmin;
        float tmax;
};

#endif