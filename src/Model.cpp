#include "Model.h"
#include <iostream> 

Model::Model() {
}

Model::~Model()
{

}

void Model::setScenegraph(IScenegraph *scenegraph) {
    this->scenegraph = scenegraph;
}

IScenegraph *Model::getScenegraph() {
    return this->scenegraph;
}