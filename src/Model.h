#ifndef __MODEL_H__
#define __MODEL_H__
#include <iostream> 

#include "sgraph/IScenegraph.h"
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

    // can be used if we wanted to add a mesh NOT via importing a txt file 
    void addMesh(util::PolygonMesh<VertexAttrib>& mesh,util::Material& mat); 

    vector<util::Material> getMaterials();
    void setScenegraph(IScenegraph *scenegraph);
    IScenegraph *getScenegraph();
    
private:
    vector<util::PolygonMesh<VertexAttrib> > meshes;
    vector<util::Material> materials;
    IScenegraph *scenegraph;
};

#endif