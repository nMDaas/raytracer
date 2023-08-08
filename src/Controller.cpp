#include "Controller.h"

#include <iostream> 
#include <fstream>

#include <ObjImporter.h>
#include "ScenegraphImporter.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

Controller::Controller(Model& m, View& v) {
    model = m;
    view = v;
}

Controller::~Controller()
{

}

void Controller::meshMaterialSetup(char* filePath, bool debugger) {
    std::cout << "filePath: " << filePath << std::endl;
    std::ifstream test(filePath); 
    if (!test)
    {
        throw runtime_error("The file doesn't exist");
    }

    ifstream inFile(filePath);
    ScenegraphImporter importer;
    if (debugger) {
        importer.addInstance("sphere","models/sphere.obj");
        importer.addInstance("box","models/box.obj");
    }
    IScenegraph *scenegraph = importer.parse(inFile);
    spdlog::debug("Scenegraph made.");
    //importer.testParse(scenegraph);

    model.setScenegraph(scenegraph);

}

void Controller::run(bool debugger)
{
    IScenegraph* scenegraph = model.getScenegraph();
    std::map<string,util::PolygonMesh<VertexAttrib> > meshes = scenegraph->getMeshes();

    view.init(this, meshes, debugger);


    while (!view.shouldWindowClose()) {
        view.display(scenegraph);
    }

    view.closeWindow();
    exit(EXIT_SUCCESS);
}

// Methods inherited from Callbacks class

void Controller::reshape(int width, int height) 
{
    cout <<"Window reshaped to width=" << width << " and height=" << height << endl;
}

void Controller::dispose()
{
    view.closeWindow();
}

void Controller::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void Controller::onkey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_R && action == 0) {
        view.raytrace();
     }
}