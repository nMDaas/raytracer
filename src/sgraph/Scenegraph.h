#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_
#include <string>
#include <map>

#include "IScenegraph.h"
#include "nodes/SGNode.h"
#include "PolygonMesh.h"
#include "../VertexAttrib.h"
#include "../objects/MeshObject.h"


/* Scenegraph implements IScenegraph */
class Scenegraph: public IScenegraph {
    protected:
      SGNode *root;
      std::map<std::string,SGNode *> nodes; // to keep track of all nodes in this scenegraph
      std::map<std::string,util::PolygonMesh<VertexAttrib> > meshes;
      std::map<std::string,MeshObject> meshObjects;
      map<string,string> meshPaths;
      glm::vec3 cameraPosition;
      glm::vec3 cameraTarget;

    public:
    Scenegraph();

    ~Scenegraph();

    // to check for copy constructors
    Scenegraph (Scenegraph &t);

    // add a node to the scenegraph to keep track of all nodes
    void addNode(const std::string& name, SGNode *node);

    void makeScenegraph(SGNode *root);

    void setMeshPaths(map<string,string>& meshPaths);

    map<string,string>& getMeshPaths();

    void setMeshes(map<string,util::PolygonMesh<VertexAttrib> >& meshes);

    void setMeshObjects(map<string,MeshObject>& in_meshObjects);

    map<string,util::PolygonMesh<VertexAttrib>>& getMeshes();

    map<string,MeshObject>& getMeshObjects();

    SGNode *getRoot();

    void setCameraPos(glm::vec3 camPos);
    void setCameraTarget(glm::vec3 camTarget);
    glm::vec3 getCameraPos();
    glm::vec3 getCameraTarget();
};

#endif