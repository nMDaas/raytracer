#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <glm/glm.hpp>

class Triangle {
    public:
        Triangle();
        ~Triangle();

        Triangle (Triangle &t); // to check for copy constructors
    private:
        glm::vec4 v0 = glm::vec4(-1.0f,-1.0f,0.0f,1.0f); 
        glm::vec4 v1 = glm::vec4(1.0f,-1.0f,0.0f,1.0f); 
        glm::vec4 v2 = glm::vec4(0.0f,1.0f,0.0f,1.0f);
        glm::vec4 e1 = v1 - v0;
        glm::vec4 e2 = v2 - v0;
        float normalX = (e1.y * e2.z) - (e1.z * e2.y);
        float normalY = (e1.z * e2.x) - (e1.x * e2.z);
        float normalZ = (e1.x * e2.y) - (e1.y * e2.x);
        glm::vec4 normal = normalize(glm::vec4(normalX,normalY,normalZ,0.0f));
        float t;
};

#endif