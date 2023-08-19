#include "Scenegraph.h"

#include <iostream>

Scenegraph::Scenegraph() {
    root = NULL;
}

Scenegraph::~Scenegraph() {
    if (root!=NULL) {
        delete root;
        root = NULL;
    }
}

// add a node to the scenegraph to keep track of all nodes
void Scenegraph::addNode(const std::string& name, SGNode *node) {
    nodes[name]=node;
}

void Scenegraph::makeScenegraph(SGNode *root) {
    this->root = root;
    if (root!=NULL) {
    this->root->setScenegraph(this);
    }
}

void Scenegraph::setMeshPaths(map<string,string>& meshPaths) {
    this->meshPaths = meshPaths;
}

map<string,string> Scenegraph::getMeshPaths() {
    return this->meshPaths;
}

void Scenegraph::setMeshes(map<string,util::PolygonMesh<VertexAttrib> >& meshes) {
    this->meshes = meshes;
}

map<string,util::PolygonMesh<VertexAttrib>>& Scenegraph::getMeshes() {
    return this->meshes;
}

SGNode* Scenegraph::getRoot() {
    return root;
}