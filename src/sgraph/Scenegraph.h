#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_
#include <string>
#include <map>

#include "IScenegraph.h"
#include "nodes/SGNode.h"
#include "PolygonMesh.h"
#include "../VertexAttrib.h"


// an implementation of IScenegraph
class Scenegraph: public IScenegraph {
    protected:
      SGNode *root;
      std::map<std::string,SGNode *> nodes; // to keep track of all nodes in this scenegraph
      std::map<std::string,util::PolygonMesh<VertexAttrib> > meshes;
      map<string,string> meshPaths;

    public:
    Scenegraph();

    ~Scenegraph();

    // add a node to the scenegraph to keep track of all nodes
    void addNode(const std::string& name, SGNode *node);

    void makeScenegraph(SGNode *root);

    void setMeshPaths(map<string,string>& meshPaths);

    map<string,string> getMeshPaths();

    void setMeshes(map<string,util::PolygonMesh<VertexAttrib> >& meshes);

    map<string,util::PolygonMesh<VertexAttrib>>& getMeshes();

    SGNode *getRoot();
};

#endif