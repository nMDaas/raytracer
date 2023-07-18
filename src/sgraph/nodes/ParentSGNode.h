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

};

#endif