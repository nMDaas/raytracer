#ifndef _SGNODE_H_
#define _SGNODE_H_
#include <string>

class IScenegraph;

/*
    This interface represents a scenegraph node.
*/
class SGNode {
    public:
    SGNode(){}
    virtual ~SGNode(){}

    // set parent of this node
    virtual void setParent(SGNode *parent)=0;

    // returns deep copy of scenegraph rooted at this node
    virtual SGNode *clone()=0;

    // set name of this node
    virtual void setName(const std::string& name)=0;
    virtual void setScenegraph(IScenegraph *graph)=0;
};

#endif