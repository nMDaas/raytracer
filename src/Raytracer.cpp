#include <iostream> 
#include "Controller.h"
#include "Model.h"
#include "View.h"


int main(void)
{
    Model model;
    View view;
    Controller controller(model, view);
    controller.meshMaterialSetup();
    //controller.run();
}