#ifndef _GROUPNODE_H_
#define _GROUPNODE_H_
#include "../IScenegraph.h"
#include "ParentSGNode.h"
#include "../SGNodeVisitor.h"
#include "SGNode.h"

class GroupNode : public ParentSGNode {
    protected:
    ParentSGNode *copyNode();

    public:
    GroupNode(const std::string& name,IScenegraph *graph);
	
    ~GroupNode();

    SGNode *clone();

    void accept(SGNodeVisitor* visitor);

};
#endif