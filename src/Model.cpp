#include "Model.h"
#include <iostream> 

Model::Model() {
}

Model::~Model()
{

}

// to check for copy constructors
Model::Model (Model &t) {
    std::cout << "MODEL COPY CONSTRUCTOR CALLED" << std::endl;
}

void Model::setScenegraph(IScenegraph *scenegraph) {
    this->scenegraph = scenegraph;
}

IScenegraph *Model::getScenegraph() {
    return this->scenegraph;
}