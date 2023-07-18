#ifndef _SCENEGRAPHIMPORTER_H_
#define _SCENEGRAPHIMPORTER_H_
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include <map>

#include "Material.h"
#include "PolygonMesh.h"
#include "VertexAttrib.h"
#include <ObjImporter.h>

#include "sgraph/IScenegraph.h"

class ScenegraphImporter {
    public:
        ScenegraphImporter();
        ~ScenegraphImporter();

        /*
        to check for copy constructors
         */
        ScenegraphImporter (ScenegraphImporter &t) {
            std::cout << "SCENEGRAPH IMPORTER COPY CONSTRUCTOR CALLED" << std::endl;
        }

        IScenegraph* parse(std::istream& input);

        private: 
        std::string stripComments(std::istream& input); // to remove lines with comments (lines starting with "#...")
        map<string,string> meshPaths; // array that stores obj filepaths in input txt file
        map<string,util::PolygonMesh<VertexAttrib> > meshes; // array that stores meshes of instances in input txt file

        void parseInstance(istream& input);
        void parseGroup(istream& input);
        void parseLeaf(istream& input);
        void parseMaterial(istream& input);
        void parseScale(istream& input);
        void parseRotate(istream& input);
        void parseTranslate(istream& input);
        void parseCopy(istream& input);
        void parseImport(istream& input);
        void parseAssignMaterial(istream& input);
        void parseAddChild(istream& input);
        void parseSetRoot(istream& input);

};

#endif