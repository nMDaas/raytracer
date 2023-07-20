#include "ScenegraphImporter.h"

ScenegraphImporter::ScenegraphImporter() {
}

ScenegraphImporter::~ScenegraphImporter()
{
    
}

std::string ScenegraphImporter::stripComments(std::istream& input) {
    std::string line;
    stringstream clean;
    while (getline(input,line)) {
        int i=0;
        while ((i<line.length()) && (line[i]!='#')) {
            clean << line[i];
            i++;
        }
        clean << endl;
    }
    return clean.str();
}

IScenegraph* ScenegraphImporter::parse(std::istream& input) {
    string inputWithOutCommentsString = stripComments(input); // remove comments
    istringstream inputWithOutComments(inputWithOutCommentsString);
    string command;
    while (inputWithOutComments >> command) {
        if (command == "instance") {
            parseInstance(inputWithOutComments);
        }
        else if (command == "group") {
            parseGroup(inputWithOutComments);
        }
        else if (command == "leaf") {
            parseLeaf(inputWithOutComments);
        }
        else if (command == "material") {
            parseMaterial(inputWithOutComments);
        }
        else if (command == "scale") {
            parseScale(inputWithOutComments);
        }
        else if (command == "rotate") {
            parseRotate(inputWithOutComments);
        }
        else if (command == "translate") {
            parseTranslate(inputWithOutComments);
        }
        else if (command == "copy") {
            parseCopy(inputWithOutComments);
        }
        else if (command == "import") {
            parseImport(inputWithOutComments);
        }
        else if (command == "assign-material") {
            parseAssignMaterial(inputWithOutComments);
        }
        else if (command == "add-child") {
            parseAddChild(inputWithOutComments);
        }
        else if (command == "assign-root") {
            parseSetRoot(inputWithOutComments);
        }
        else {
            throw runtime_error("Unrecognized or out-of-place command: "+command);
        }
    }

}

void ScenegraphImporter::parseInstance(istream& input) {
    string name,path;
    input >> name >> path;
    std::cout << "command: instance " << name << " " << path << std::endl;
    meshPaths[name] = path;
    ifstream in(path);
    if (in.is_open()) {
        util::PolygonMesh<VertexAttrib> mesh = util::ObjImporter<VertexAttrib>::importFile(in,false);
        meshes[name] = mesh;         
        } 
}

void ScenegraphImporter::parseGroup(istream& input) {
    string varname,name;
    input >> varname >> name;
    std::cout << "command: group " << varname << " " << name << std::endl;
    SGNode *group = new GroupNode(name,NULL);
    nodes[varname] = group;
}

void ScenegraphImporter::parseLeaf(istream& input) {
    string varname,name,command,instanceof;
    input >> varname >> name >> command;
    if (command == "instanceof") {
        input >> instanceof;
    }
    std::cout << "command: leaf " << varname << " " << name << " " << command << " " << instanceof << std::endl;
    SGNode *leaf = new LeafNode(instanceof,name,NULL);
    nodes[varname] = leaf;
}

void ScenegraphImporter::parseMaterial(istream& input) {
    util::Material mat;
    float r,g,b;
    string name;
    input >> name;
    string command;
    input >> command;
    std::cout << "command: material " << name << std::endl;
    while (command!="end-material") {
        if (command == "ambient") {
            input >> r >> g >> b;
            std::cout << "ambient: " << r << " " << g << " " << b << std::endl;
            mat.setAmbient(r,g,b);
        }
        else if (command == "diffuse") {
            input >> r >> g >> b;
            std::cout << "diffuse: " << r << " " << g << " " << b << std::endl;
            mat.setDiffuse(r,g,b);
        }
        else if (command == "specular") {
            input >> r >> g >> b;
            std::cout << "specular: " << r << " " << g << " " << b << std::endl;
            mat.setSpecular(r,g,b);
        }
        else if (command == "emission") {
            input >> r >> g >> b;
            std::cout << "emission: " << r << " " << g << " " << b << std::endl;
            mat.setEmission(r,g,b);
        }
        else if (command == "shininess") {
            input >> r;
            std::cout << "shininess: " << r  << std::endl;
            mat.setShininess(r);
        }
        input >> command;
    }
     materials[name] = mat;
}

void ScenegraphImporter::parseScale(istream& input) {
    string varname,name;
    input >> varname >> name;
    float sx,sy,sz;
    input >> sx >> sy >> sz;
    std::cout << "command: scale " << varname << " " << name << " " << sx << " " << sy << " " << sz << std::endl;
    SGNode *scaleNode = new ScaleTransform(sx,sy,sz,name,NULL);
    nodes[varname] = scaleNode;
}

void ScenegraphImporter::parseRotate(istream& input) {
    string varname,name;
    input >> varname >> name;
    float angleInDegrees,ax,ay,az;
    input >> angleInDegrees >> ax >> ay >> az;
    std::cout << "command: rotate " << varname << " " << name << " " << angleInDegrees << " " << ax << " " << ay << " " << az <<std::endl;
    SGNode *rotateNode = new RotateTransform(glm::radians(angleInDegrees),ax,ay,az,name,NULL);
    nodes[varname] = rotateNode;  
}

void ScenegraphImporter::parseTranslate(istream& input) {
    string varname,name;
    input >> varname >> name;
    float tx,ty,tz;
    input >> tx >> ty >> tz;
    std::cout << "command: translate " << varname << " " << name << " " << tx << " " << ty << " " << tz << std::endl;
    SGNode *translateNode = new TranslateTransform(tx,ty,tz,name,NULL);
    nodes[varname] = translateNode;  
}

void ScenegraphImporter::parseCopy(istream& input) {
    string nodename,copyof;
    input >> nodename >> copyof;
    std::cout << "command: copy " << nodename << " " << copyof << std::endl;
    if (nodes.find(copyof)!=nodes.end()) {
        SGNode * copy = nodes[copyof]->clone();
        nodes[nodename] = copy;
    }
}

void ScenegraphImporter::parseImport(istream& input) {
    string nodename,filepath;
    input >> nodename >> filepath;
    std::cout << "command: import " << nodename << " " << filepath << std::endl;
}

void ScenegraphImporter::parseAssignMaterial(istream& input) {
    string nodename,matname;
    input >> nodename >> matname;
    std::cout << "command: assign-material " << nodename << " " << matname << std::endl;
    LeafNode *leafNode = dynamic_cast<LeafNode *>(nodes[nodename]);
    if ((leafNode!=NULL) && (materials.find(matname)!=materials.end())) {
        leafNode->setMaterial(materials[matname]);
    }
}

void ScenegraphImporter::parseAddChild(istream& input) {
    string childname,parentname;
    input >> childname >> parentname;
    std::cout << "command: add-child" << " " << childname << " " << parentname << std::endl;

    // find parent node in array and cast to parentSGNode
    ParentSGNode * parentNode = dynamic_cast<ParentSGNode *>(nodes[parentname]);
    SGNode * childNode = NULL;
    // if the child node is found in array, set childNode
     if (nodes.find(childname)!=nodes.end()) {
        childNode = nodes[childname];
     }

    // if parent node and child node are not invalid, set parent of child node to be parent node
    if ((parentNode!=NULL) && (childNode!=NULL)) {
        parentNode->addChild(childNode);
    }
}

void ScenegraphImporter::parseSetRoot(istream& input) {
    string rootname;
    input >> rootname;
    std::cout << "command: assign-root " << rootname << std::endl;
    root = nodes[rootname];
}