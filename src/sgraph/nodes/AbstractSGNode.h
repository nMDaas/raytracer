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
    AbstractSGNode(const std::string& name,IScenegraph *graph);

    // to check for copy constructors
    AbstractSGNode (AbstractSGNode &t);

    // set parent of this node
    void setParent(SGNode *parent);

    // set name of this node
    void setName(const std::string& name);

    std::string getName();
    void setScenegraph(IScenegraph *graph);

};

#endif