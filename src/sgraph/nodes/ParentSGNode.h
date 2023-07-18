#ifndef _PARENTSGNODE_H_
#define _PARENTSGNODE_H_
#include <iostream>

#include "../IScenegraph.h"
#include "AbstractSGNode.h"

/*
    This class represents a SGNode that can have children.
*/
class ParentSGNode: public AbstractSGNode {

    public:
        ParentSGNode(const std::string& name,IScenegraph *scenegraph)
        : AbstractSGNode(name,scenegraph) {}

        ~ParentSGNode() {
        }

        /*
        to check for copy constructors
        */
        ParentSGNode (ParentSGNode &t) {
            std::cout << "PARENT NODE COPY CONSTRUCTOR CALLED" << std::endl;
        }

};

#endif