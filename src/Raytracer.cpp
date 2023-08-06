#include <iostream> 
#include "Controller.h"
#include "Model.h"
#include "View.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"


int main(int argc,char *argv[])
{
    spdlog::cfg::load_env_levels();
    Model model;
    View view;
    Controller controller(model, view);

    controller.meshMaterialSetup(argv[1]);

    // when running via debug: 
    // controller.meshMaterialSetup("scenegraphs/firstScene.txt");

    // when running via terminal: 
    // controller.meshMaterialSetup("src/scenegraphs/simpleScene.txt");

    controller.run();
}