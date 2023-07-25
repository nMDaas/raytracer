#ifndef _PARENTSGNODE_H_
#define _PARENTSGNODE_H_
#include <iostream>
#include <vector>

#include "../IScenegraph.h"
#include "AbstractSGNode.h"

/*
    This class represents a SGNode that can have children.
*/
class ParentSGNode: public AbstractSGNode {

    protected:
        std::vector<SGNode *> children;

    public:
        ParentSGNode(const std::string& name,IScenegraph *scenegraph)
        : AbstractSGNode(name,scenegraph) {}

        ~ParentSGNode() {
            for (int i=0;i<children.size();i++) {
                delete children[i];
            }
        }

        // add another child to this node
        virtual void addChild(SGNode *child)=0;

        virtual ParentSGNode *copyNode()=0;

        SGNode *clone() {
            ParentSGNode * newtransform = copyNode();

            for (int i=0;i<children.size();i=i+1) {
                    newtransform->addChild(children[i]->clone());
            }

            return newtransform;
        }

        vector<SGNode *> getChildren() {
            return children;
        }
};

#endif