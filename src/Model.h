#ifndef __MODEL_H__
#define __MODEL_H__
#include <iostream> 

#include "PolygonMesh.h"
#include "VertexAttrib.h"
#include "Material.h"

class Model 
{
public:
    Model();
    ~Model();

    /*
        to check for copy constructors
    */
    Model (Model &t) {
        std::cout << "MODEL COPY CONSTRUCTOR CALLED" << std::endl;
    }

    void addMesh(util::PolygonMesh<VertexAttrib>& mesh,util::Material& mat);
    
private:
    vector<util::PolygonMesh<VertexAttrib> > meshes;
    vector<util::Material> materials;
};

#endif