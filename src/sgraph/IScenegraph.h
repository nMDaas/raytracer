#ifndef _ISCENEGRAPH_H_
#define _ISCENEGRAPH_H_
#include <string>
#include <map>

#include "nodes/SGNode.h"
#include "PolygonMesh.h"
#include "../VertexAttrib.h"

/*
    This is an abstract class.
*/
class IScenegraph {
    // add a node to the scenegraph to keep track of all nodes
    public:
    virtual void addNode(const std::string& name,SGNode *node)=0;
    virtual std::map<std::string,util::PolygonMesh<VertexAttrib>> getMeshes()=0;
};

#endif