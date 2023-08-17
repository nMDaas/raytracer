#ifndef __BOX_H__
#define __BOX_H__

#include <glm/glm.hpp>

class Box {
    public:
        Box();
        ~Box();

        Box (Box &t); // to check for copy constructors

};

#endif