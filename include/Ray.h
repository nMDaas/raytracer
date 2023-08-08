#ifndef ___RAY_H___
#define ___RAY_H___

#include "glm/glm.hpp"

class Ray
{
    public:
        Ray(glm::vec4 i_origin, glm::vec4 i_direction)
        : origin(i_origin), direction(i_direction) {}

        ~Ray() {}

    private:
        glm::vec4 origin; // points have glm::vec4(x,y,z,1)
        glm::vec4 direction; // vectors have glm::vec4(x,y,z,0)

};
#endif


