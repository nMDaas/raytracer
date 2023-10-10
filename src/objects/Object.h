#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <glm/glm.hpp>

/* This object is for non primitive objects that are made up of triangles */
class Object {
    public:
        Object();
        ~Object();

        Object (Object &t); // to check for copy constructors

    private:
};

#endif