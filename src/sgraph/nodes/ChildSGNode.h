#ifndef _CHILDSGNODE_H_
#define _CHILDSGNODE_H_

#include "../IScenegraph.h"
#include "AbstractSGNode.h"

class ChildSGNode: public AbstractSGNode {
    public: 
    ChildSGNode(const std::string& name,IScenegraph *scenegraph);

    ~ChildSGNode();

};

#endif