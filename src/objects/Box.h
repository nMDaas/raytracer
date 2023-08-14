#ifndef __BOX_H__
#define __BOX_H__

#include <glm/glm.hpp>

class Box {
public:
    Box();
    ~Box();

    // to check for copy constructors
    Box (Box &t);
    float getTime(glm::vec4 s, glm::vec4 v);

};

#endif