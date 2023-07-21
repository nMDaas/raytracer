#include "Model.h"
#include <iostream> 

Model::Model() {
}

Model::~Model()
{

}

void Model::addMesh(util::PolygonMesh<VertexAttrib>& mesh,util::Material& mat) {
    meshes.push_back(mesh);
    materials.push_back(mat);
}

vector<util::PolygonMesh<VertexAttrib> > Model::getMeshes() {
    return meshes;
}

vector<util::Material> Model::getMaterials() {
    return materials;
}

void Model::setScenegraph(IScenegraph *scenegraph) {
    this->scenegraph = scenegraph;
}

IScenegraph *Model::getScenegraph() {
    return this->scenegraph;
}