#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>

#include "Model.h"
#include "View.h"

#include "PolygonMesh.h"
#include "VertexAttrib.h"
#include "Material.h"

class Controller
{
public:
    Controller(Model& m, View& v);
    ~Controller();

    /*
        to check for copy constructors
    */
    Controller (Controller &t) {
        std::cout << "CONTROLLER COPY CONSTRUCTOR CALLED" << std::endl;
    }

    void meshMaterialSetup();
    void run();

private:
    Model model;
    View view;
};

#endif