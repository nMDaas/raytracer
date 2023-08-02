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

    // when running via debug: 
    //controller.meshMaterialSetup("scenegraphs/simpleScene.txt");

    // when running via terminal: 
    // controller.meshMaterialSetup("src/scenegraphs/simpleScene.txt");

    controller.run();
}