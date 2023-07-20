#ifndef _ABSTRACTSGNODE_H_
#define _ABSTRACTSGNODE_H_
#include <iostream>

#include "../IScenegraph.h"
#include "SGNode.h"

/*
    This class implements the SGNode interface
*/
class AbstractSGNode : public SGNode {
    protected: 
    SGNode *parent;
    
    public:
    AbstractSGNode(const std::string& name,IScenegraph *graph) {
    }

    // set parent of this node
    void setParent(SGNode *parent) {
      this->parent = parent;
    }

};

#endif