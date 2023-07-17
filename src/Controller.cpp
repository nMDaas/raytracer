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

void Controller::meshMaterialSetup() {

    ifstream inFile("scenegraphs/firstScene.txt");
    ScenegraphImporter importer;
    IScenegraph *scenegraph = importer.parse(inFile);
    cout << "Scenegraph made" << endl;   

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
    vector<util::PolygonMesh<VertexAttrib> > meshes = model.getMeshes();
    vector<util::Material> materials = model.getMaterials();
    view.init(meshes, materials);

    while (!view.shouldWindowClose()) {
        view.display();
    }

    view.closeWindow();
    exit(EXIT_SUCCESS);
}