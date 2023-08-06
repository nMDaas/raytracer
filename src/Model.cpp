#include "Model.h"
#include <iostream> 

Model::Model() {
}

Model::~Model()
{

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