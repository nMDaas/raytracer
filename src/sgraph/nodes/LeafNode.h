#ifndef _LEAFNODE_H_
#define _LEAFNODE_H_

#include "Material.h"

#include "AbstractSGNode.h"
#include "../IScenegraph.h"

class LeafNode: public AbstractSGNode {
    public: 
    LeafNode(const std::string& instanceOf,util::Material& material,const std::string& name,IScenegraph *graph)
        :AbstractSGNode(name,graph) {
    }

    LeafNode(const std::string& instanceOf,const std::string& name,IScenegraph *graph)
        :AbstractSGNode(name,graph) {
    }
	
	~LeafNode(){}
};

#endif