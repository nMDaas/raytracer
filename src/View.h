#ifndef __VIEW_H__
#define __VIEW_H__
#include <iostream>

#include "PolygonMesh.h"
#include "VertexAttrib.h"
#include "Material.h"

class View
{
    
public:
    View();
    ~View();

    /*
        to check for copy constructors
    */
    View (View &t) {
        std::cout << "VIEW COPY CONSTRUCTOR CALLED" << std::endl;
    }

    void init(vector<util::PolygonMesh<VertexAttrib>>& meshes,vector<util::Material>& materials);

private:
};

#endif