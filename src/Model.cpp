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