#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <glm/glm.hpp>

class Sphere {
    public:
        Sphere();
        ~Sphere();

        Sphere (Sphere &t); // to check for copy constructors

        bool calcTimes(glm::vec4 s, glm::vec4 v); // calculates tmin and tmax of a ray's intersection with a unit sphere
        float getTime(); // returns the time of first intersection of the ray with the unit box
        glm::vec4 getNormal(glm::vec4 intersectionPoint);
        glm::vec2 getTextureCoordinates(glm::vec4 intersectionPoint);

    private:
        float tmin;
        float tmax;
};

#endif