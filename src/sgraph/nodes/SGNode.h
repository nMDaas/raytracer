#ifndef _SGNODE_H_
#define _SGNODE_H_

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
    virtual void setName(const string& name)=0;
};

#endif