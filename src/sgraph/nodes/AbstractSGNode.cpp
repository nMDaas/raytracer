#include "AbstractSGNode.h"

AbstractSGNode::AbstractSGNode(const std::string& name,IScenegraph *graph) {
    this->parent = NULL;
    scenegraph = graph;
    setName(name);
}

// to check for copy constructors
AbstractSGNode::AbstractSGNode (AbstractSGNode &t) {
    std::cout << "ABSTRACTSGNODE COPY CONSTRUCTOR CALLED" << std::endl;
}

// set parent of this node
void AbstractSGNode::setParent(SGNode *parent) {
    this->parent = parent;
}

// set name of this node
void AbstractSGNode::setName(const std::string& name) {
    this->name = name;
}

std::string AbstractSGNode::getName() { 
    return name;
}

void AbstractSGNode::setScenegraph(IScenegraph *graph) {
    this->scenegraph = graph;
    graph->addNode(this->name,this);
}