#ifndef _LIGHTNODE_H_
#define __LIGHTNODE_H_

#include "Light.h"

#include "ChildSGNode.h"
#include "../IScenegraph.h"
#include "SGNode.h"

class LightNode: public ChildSGNode {
    protected: 
    util::Light light;

    public: 
    LightNode(const std::string& name,IScenegraph *graph);

    SGNode *clone();

    void accept(SGNodeVisitor* visitor);
};

#endif