#include "Controller.h"

#include <iostream> 
#include <fstream>

#include <ObjImporter.h>
#include "ScenegraphImporter.h"

Controller::Controller(Model& m, View& v) {
    model = m;
    view = v;
}

Controller::~Controller()
{

}

void Controller::meshMaterialSetup(char* filePath) {

    ifstream inFile(filePath);
    ScenegraphImporter importer;
    IScenegraph *scenegraph = importer.parse(inFile);
    cout << "Scenegraph made" << endl;   
    //importer.testParse(scenegraph);

    model.setScenegraph(scenegraph);

    /*
    util::PolygonMesh<VertexAttrib> mesh;

    //import an OBJ model from file
    ifstream in("models/box.obj");
    mesh = util::ObjImporter<VertexAttrib>::importFile(in,true);

    //give a material for it.
    util::Material material;
    material.setAmbient(1,1,1);
    material.setDiffuse(1,1,1);
    material.setSpecular(1,1,1);
    
    model.addMesh(mesh,material);
    */

}

void Controller::run()
{
    IScenegraph* scenegraph = model.getScenegraph();
    std::map<string,util::PolygonMesh<VertexAttrib> > meshes = scenegraph->getMeshes();

    vector<util::Material> materials = model.getMaterials();
    view.init(this, meshes);

    /*
    while (!view.shouldWindowClose()) {
        view.display();
    }

    view.closeWindow(); */
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

void Controller::onkey(int key, int scancode, int action, int mods) {}