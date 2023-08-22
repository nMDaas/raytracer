#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <glm/glm.hpp>

class Sphere {
    public:
        Sphere();
        ~Sphere();

        Sphere (Sphere &t); // to check for copy constructors

    private:
};

#endif