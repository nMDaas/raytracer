#ifndef _PARENTSGNODE_H_
#define _PARENTSGNODE_H_
#include <vector>

#include "../IScenegraph.h"
#include "AbstractSGNode.h"
#include "SGNode.h"

/*
    This class represents a SGNode that can have children.
*/
class ParentSGNode: public AbstractSGNode {

    protected:
        std::vector<SGNode *> children;

    public:
        ParentSGNode(const std::string& name,IScenegraph *scenegraph);

        ~ParentSGNode();

        // add another child to this node
        void addChild(SGNode *child);

        void setScenegraph(IScenegraph *graph);

        virtual ParentSGNode *copyNode()=0;

        SGNode *clone();

        vector<SGNode *> getChildren();
};

#endif