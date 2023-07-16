#ifndef OBJECT_H_
#define OBJECT_H_

#include "ObjectInstance.h"
#include "Material.h"

class Object {
    public:
        util::ObjectInstance object;
        util::Material material;
        Object() 
        :object("temp") {
            
        }
};

#endif