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
#include <glm/gtx/string_cast.hpp>
#include "TextureImage.h"

#include "sgraph/IScenegraph.h"
#include "sgraph/Scenegraph.h"
#include "sgraph/nodes/SGNode.h"
#include "sgraph/nodes/ParentSGNode.h"
#include "sgraph/nodes/AbstractSGNode.h"
#include "sgraph/nodes/GroupNode.h"
#include "sgraph/nodes/ChildSGNode.h"
#include "sgraph/nodes/LeafNode.h"
#include "sgraph/nodes/LightNode.h"
#include "sgraph/nodes/TransformNode.h"
#include "sgraph/nodes/ScaleTransform.h"
#include "sgraph/nodes/RotateTransform.h"
#include "sgraph/nodes/TranslateTransform.h"

class ScenegraphImporter {
    public:
        ScenegraphImporter();
        ~ScenegraphImporter();

        // to check for copy constructors
        ScenegraphImporter (ScenegraphImporter &t);

        IScenegraph* parse(std::istream& input);
        void testParse(IScenegraph* scenegraph);
        void addInstance(string name, string path); // to manually add instances when using debugger

        private: 
        std::string stripComments(std::istream& input); // to remove lines with comments (lines starting with "#...")
        map<string,string> meshPaths; // array that stores obj filepaths in input txt file
        map<string,util::PolygonMesh<VertexAttrib> > meshes; // array that stores meshes of instances in input txt file
        map<string,SGNode *> nodes;
        map<string,util::Material> materials;
        SGNode *root;
        map<string,util::TextureImage *> textureObjects;

        void parseInstance(istream& input);
        void parseGroup(istream& input);
        void parseLeaf(istream& input);
        void parseLight(istream& input);
        void parseMaterial(istream& input);
        void parseScale(istream& input);
        void parseRotate(istream& input);
        void parseTranslate(istream& input);
        void parseCopy(istream& input);
        void parseImport(istream& input);
        void parseAssignMaterial(istream& input);
        void parseAddChild(istream& input);
        void parseSetRoot(istream& input);
        void parseTexture(istream& input);
        void parseAssignTexture(istream& input);

};

#endif