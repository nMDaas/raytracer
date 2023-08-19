#ifndef _LEAFNODE_H_
#define _LEAFNODE_H_

#include "Material.h"

#include "ChildSGNode.h"
#include "../IScenegraph.h"
#include "SGNode.h"

class LeafNode: public ChildSGNode {
    protected: 
    util::Material material;
    string objInstanceName;

    public: 
    LeafNode(const std::string& instanceOf,util::Material& material,const std::string& name,IScenegraph *graph);

    LeafNode(const std::string& instanceOf,const std::string& name,IScenegraph *graph);

    // sets material of all vertices in this object
    void setMaterial(const util::Material& mat);

    SGNode *clone();

    string getInstanceOf();

    util::Material* getMaterial();

    void accept(SGNodeVisitor* visitor);
};

#endif