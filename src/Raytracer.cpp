#include <iostream> 
#include "Controller.h"
#include "Model.h"
#include "View.h"


int main(int argc,char *argv[])
{
    Model model;
    View view;
    Controller controller(model, view);
    controller.meshMaterialSetup(argv[1]);
    //controller.run();
}