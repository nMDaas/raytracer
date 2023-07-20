#ifndef _ISCENEGRAPH_H_
#define _ISCENEGRAPH_H_
#include <string>

#include "nodes/SGNode.h"

/*
    This is an abstract class.
*/
class IScenegraph {
    // add a node to the scenegraph to keep track of all nodes
    virtual void addNode(const std::string& name,SGNode *node)=0;
};

#endif