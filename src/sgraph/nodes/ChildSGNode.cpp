#include "ChildSGNode.h"

ChildSGNode::ChildSGNode(const std::string& name,IScenegraph *scenegraph)
: AbstractSGNode(name,scenegraph) {}

ChildSGNode::~ChildSGNode(){}