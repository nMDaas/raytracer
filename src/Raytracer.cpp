#include <iostream> 
#include "Controller.h"
#include "Model.h"
#include "View.h"
#include "ObjImporter.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"


int main(int argc,char *argv[])
{
    spdlog::cfg::load_env_levels();
    Model model;
    View view;
    Controller controller(model, view);

    string filePath = "src/models/boxMaya.obj";
    string file = filePath;
    std::ifstream test(filePath); 
    if (!test)
    {
        throw runtime_error("The file doesn't exist");
    }

    ifstream inFile(filePath);
    ObjImporter objImporter;

    objImporter.parseObjFile(inFile);

    /*
    if (argc > 1) {
        // run via terminal
        controller.meshMaterialSetup(argv[1], false);
    }
    else {
        // run via debugger
        controller.meshMaterialSetup("scenegraphs/areaLightsSoftShadowTest.txt", true);
    }
    controller.run(); */
}