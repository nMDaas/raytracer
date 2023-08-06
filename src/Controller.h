#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>

#include "Model.h"
#include "View.h"

#include "PolygonMesh.h"
#include "VertexAttrib.h"
#include "Material.h"

class Controller: public Callbacks
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

    void meshMaterialSetup(char* filePath, bool debugger);
    void run(bool debugger);

    virtual void reshape(int width, int height);
    virtual void dispose();
    virtual void onkey(int key, int scancode, int action, int mods);
    virtual void error_callback(int error, const char* description);

private:
    Model model;
    View view;
};

#endif