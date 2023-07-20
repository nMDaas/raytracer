#ifndef _PARENTSGNODE_H_
#define _PARENTSGNODE_H_
#include <iostream>
#include <vector>

#include "../IScenegraph.h"
#include "AbstractSGNode.h"

/*
    This class represents a SGNode that can have children.
*/
class ParentSGNode: public AbstractSGNode {

    protected:
        vector<SGNode *> children;

    public:
        ParentSGNode(const std::string& name,IScenegraph *scenegraph)
        : AbstractSGNode(name,scenegraph) {}

        ~ParentSGNode() {
        }

        // add another child to this node
        virtual void addChild(SGNode *child)=0;

};

#endif