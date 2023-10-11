#ifndef _CHILDSGNODE_H_
#define _CHILDSGNODE_H_

#include "../IScenegraph.h"
#include "AbstractSGNode.h"

/* an ChildSGNode is abstract class that extends AbstractSGNode */
class ChildSGNode: public AbstractSGNode {
    public: 
    ChildSGNode(const std::string& name,IScenegraph *scenegraph);

    ~ChildSGNode();

};

#endif