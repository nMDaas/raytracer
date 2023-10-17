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

// to check for copy constructors
Scenegraph::Scenegraph (Scenegraph &t) {
    std::cout << "SCENEGRAPH COPY CONSTRUCTOR CALLED" << std::endl;
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

map<string,string>& Scenegraph::getMeshPaths() {
    return this->meshPaths;
}

void Scenegraph::setMeshes(map<string,util::PolygonMesh<VertexAttrib> >& meshes) {
    this->meshes = meshes;
}

void Scenegraph::setMeshObjects(map<string,MeshObject>& in_meshObjects) {
    meshObjects = std::move(in_meshObjects);
}

map<string,util::PolygonMesh<VertexAttrib>>& Scenegraph::getMeshes() {
    return this->meshes;
}

map<string,MeshObject>& Scenegraph::getMeshObjects() {
    return this->meshObjects;
}

void Scenegraph::setCameraPos(glm::vec3 camPos) {
    cameraPosition = camPos;
}

void Scenegraph::setCameraTarget(glm::vec3 camTarget) {
    cameraTarget = camTarget;
}

glm::vec3 Scenegraph::getCameraPos() {
    return cameraPosition;
}

glm::vec3 Scenegraph::getCameraTarget() {
    return cameraTarget;
}

SGNode* Scenegraph::getRoot() {
    return root;
}