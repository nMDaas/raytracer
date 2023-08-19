#include "LeafNode.h"

LeafNode::LeafNode(const std::string& instanceOf,util::Material& material,const std::string& name,IScenegraph *graph)
    :ChildSGNode(name,graph) {
    this->objInstanceName = instanceOf;
    this->material = material;
}

LeafNode::LeafNode(const std::string& instanceOf,const std::string& name,IScenegraph *graph)
    :ChildSGNode(name,graph) {
    this->objInstanceName = instanceOf;
}

// sets material of all vertices in this object
void LeafNode::setMaterial(const util::Material& mat) {
    material = mat;
}

SGNode* LeafNode::clone() {
    LeafNode *newclone = new LeafNode(this->objInstanceName,material,name,scenegraph);
    return newclone;
}

string LeafNode::getInstanceOf() {
    return this->objInstanceName;
}

util::Material* LeafNode::getMaterial()
{
    return &material;
}

void LeafNode::accept(SGNodeVisitor* visitor) {
    visitor->visitLeafNode(this);
}