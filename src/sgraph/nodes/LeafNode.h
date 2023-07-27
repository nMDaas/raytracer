#ifndef _LEAFNODE_H_
#define _LEAFNODE_H_

#include "Material.h"

#include "AbstractSGNode.h"
#include "../IScenegraph.h"

class LeafNode: public AbstractSGNode {
    protected: 
    util::Material material;
    string objInstanceName;

    public: 
    LeafNode(const std::string& instanceOf,util::Material& material,const std::string& name,IScenegraph *graph)
        :AbstractSGNode(name,graph) {
        this->objInstanceName = instanceOf;
        this->material = material;
    }

    LeafNode(const std::string& instanceOf,const std::string& name,IScenegraph *graph)
        :AbstractSGNode(name,graph) {
        this->objInstanceName = instanceOf;
    }
	
	~LeafNode(){}

    // sets material of all vertices in this object
    void setMaterial(const util::Material& mat) {
        material = mat;
    }

    SGNode *clone() {
        LeafNode *newclone = new LeafNode(this->objInstanceName,material,name,scenegraph);
        return newclone;
    }

    string getInstanceOf() {
        return this->objInstanceName;
    }

    util::Material getMaterial()
    {
        return material;
    }

    void accept(SGNodeVisitor* visitor) {
      
    }
};

#endif