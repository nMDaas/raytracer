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

// to check for copy constructors
Controller::Controller (Controller &t) {
    std::cout << "CONTROLLER COPY CONSTRUCTOR CALLED" << std::endl;
}

void Controller::meshMaterialSetup(char* filePath, bool debugger) {
    string file = filePath;
    spdlog::debug("filePath: " + file);
    std::ifstream test(filePath); 
    if (!test)
    {
        throw runtime_error("The file doesn't exist");
    }

    ifstream inFile(filePath);
    IScenegraph *scenegraph;

    if (debugger) {
        ScenegraphImporter importer(true);
        importer.addInstance("sphere","models/sphere.obj");
        importer.addInstance("box","models/box.obj");
        importer.addInstance("cylinder","models/cylinder.obj");
        debugging = true;
        scenegraph = importer.parse(inFile);
        //importer.testParse(scenegraph);
    }
    else {
        ScenegraphImporter importer(false);
        debugging = false;
        scenegraph = importer.parse(inFile);
        //importer.testParse(scenegraph);
    }
    spdlog::debug("Scenegraph made.");

    model.setScenegraph(scenegraph);

}

void Controller::run()
{
    IScenegraph* scenegraph = model.getScenegraph();
    std::map<string,util::PolygonMesh<VertexAttrib>>& meshes = scenegraph->getMeshes();
    glm::vec3 cameraPosition = scenegraph->getCameraPos();
    glm::vec3 cameraTarget = scenegraph->getCameraTarget();

    view.init(this, meshes, debugging,cameraPosition,cameraTarget);


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
        IScenegraph* scenegraph = model.getScenegraph();
        view.raytrace(debugging,scenegraph);
     }
}