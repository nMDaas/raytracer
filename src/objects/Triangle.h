#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <glm/glm.hpp>

class Triangle {
    public:
        Triangle();
        Triangle(glm::vec4 v0_in, glm::vec4 v1_in, glm::vec4 v2_in);
        ~Triangle();

       // Triangle (Triangle &t); // to check for copy constructors
        bool calcTimes(glm::vec4 s, glm::vec4 v); // calculates time of a ray's intersection with a triangle
        float getTime(); // returns the time of first intersection of the ray with the triangle
        glm::vec4 getNormal(glm::vec4 intersectionPoint);
        glm::vec2 getTextureCoordinates(glm::vec4 intersectionPoint);
        bool pointInsideTriangle(glm::vec4 intersectionPoint);

    private:
        glm::vec4 v0; 
        glm::vec4 v1; 
        glm::vec4 v2;
        glm::vec4 e1;
        glm::vec4 e2;
        glm::vec4 normal;
        float t;
        glm::vec4 getCrossProduct(glm::vec4 vec1, glm::vec4 vec2);
};

#endif