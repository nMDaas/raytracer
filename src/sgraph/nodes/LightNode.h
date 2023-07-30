#ifndef _LIGHTNODE_H_
#define __LIGHTNODE_H_

#include "ChildSGNode.h"
#include "../IScenegraph.h"
#include "SGNode.h"

class LightNode: public ChildSGNode {
    protected: 

    public: 
    LightNode(const std::string& name,IScenegraph *graph);

    SGNode *clone();

    void accept(SGNodeVisitor* visitor);
};

#endif