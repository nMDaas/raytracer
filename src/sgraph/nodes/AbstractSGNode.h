#ifndef _ABSTRACTSGNODE_H_
#define _ABSTRACTSGNODE_H_
#include <iostream>
#include <string>

#include "../IScenegraph.h"
#include "SGNode.h"

/*
    This class implements the SGNode interface
*/
class AbstractSGNode : public SGNode {
    protected: 
    std::string name;
    SGNode *parent;
    IScenegraph *scenegraph;

    public:
    AbstractSGNode(const std::string& name,IScenegraph *graph) {
    }

    // set parent of this node
    void setParent(SGNode *parent) {
      this->parent = parent;
    }

    // set name of this node
    void setName(const std::string& name) {
      this->name = name;
    }

};

#endif