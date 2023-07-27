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

    if (root!=NULL) {
        IScenegraph *scenegraph = new Scenegraph();
        scenegraph->makeScenegraph(root);
        scenegraph->setMeshes(meshes);
        scenegraph->setMeshPaths(meshPaths);
        return scenegraph;
    }
    else {
        throw runtime_error("Parsed scene graph, but nothing set as root");
    }

}

void ScenegraphImporter::parseInstance(istream& input) {
    string name,path;
    input >> name >> path;
    //std::cout << "command: instance " << name << " " << path << std::endl;
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
    SGNode *group = new GroupNode(name,NULL);
    nodes[varname] = group;
}

void ScenegraphImporter::parseLeaf(istream& input) {
    string varname,name,command,instanceof;
    input >> varname >> name >> command;
    if (command == "instanceof") {
        input >> instanceof;
    }
    //std::cout << "command: leaf " << varname << " " << name << " " << command << " " << instanceof << std::endl;
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
    //std::cout << "command: material " << name << std::endl;
    while (command!="end-material") {
        if (command == "ambient") {
            input >> r >> g >> b;
            //std::cout << "ambient: " << r << " " << g << " " << b << std::endl;
            mat.setAmbient(r,g,b);
        }
        else if (command == "diffuse") {
            input >> r >> g >> b;
            //std::cout << "diffuse: " << r << " " << g << " " << b << std::endl;
            mat.setDiffuse(r,g,b);
        }
        else if (command == "specular") {
            input >> r >> g >> b;
            //std::cout << "specular: " << r << " " << g << " " << b << std::endl;
            mat.setSpecular(r,g,b);
        }
        else if (command == "emission") {
            input >> r >> g >> b;
            //std::cout << "emission: " << r << " " << g << " " << b << std::endl;
            mat.setEmission(r,g,b);
        }
        else if (command == "shininess") {
            input >> r;
            //std::cout << "shininess: " << r  << std::endl;
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
    //std::cout << "command: scale " << varname << " " << name << " " << sx << " " << sy << " " << sz << std::endl;
    SGNode *scaleNode = new ScaleTransform(sx,sy,sz,name,NULL);
    nodes[varname] = scaleNode;
}

void ScenegraphImporter::parseRotate(istream& input) {
    string varname,name;
    input >> varname >> name;
    float angleInDegrees,ax,ay,az;
    input >> angleInDegrees >> ax >> ay >> az;
    //std::cout << "command: rotate " << varname << " " << name << " " << angleInDegrees << " " << ax << " " << ay << " " << az <<std::endl;
    SGNode *rotateNode = new RotateTransform(glm::radians(angleInDegrees),ax,ay,az,name,NULL);
    nodes[varname] = rotateNode;  
}

void ScenegraphImporter::parseTranslate(istream& input) {
    string varname,name;
    input >> varname >> name;
    float tx,ty,tz;
    input >> tx >> ty >> tz;
    //std::cout << "command: translate " << varname << " " << name << " " << tx << " " << ty << " " << tz << std::endl;
    SGNode *translateNode = new TranslateTransform(tx,ty,tz,name,NULL);
    nodes[varname] = translateNode;  
}

void ScenegraphImporter::parseCopy(istream& input) {
    string nodename,copyof;
    input >> nodename >> copyof;
    //std::cout << "command: copy " << nodename << " " << copyof << std::endl;
    if (nodes.find(copyof)!=nodes.end()) {
        SGNode * copy = nodes[copyof]->clone();
        nodes[nodename] = copy;
    }
    else {
        throw runtime_error("Node with name \""+copyof+"\" not found");
    }
}

void ScenegraphImporter::parseImport(istream& input) {
    string nodename,filepath;
    input >> nodename >> filepath;
    //std::cout << "command: import " << nodename << " " << filepath << std::endl;
}

void ScenegraphImporter::parseAssignMaterial(istream& input) {
    string nodename,matname;
    input >> nodename >> matname;
    //std::cout << "command: assign-material " << nodename << " " << matname << std::endl;
    LeafNode *leafNode = dynamic_cast<LeafNode *>(nodes[nodename]);
    if ((leafNode!=NULL) && (materials.find(matname)!=materials.end())) {
        leafNode->setMaterial(materials[matname]);
    }
    else if (leafNode==NULL) {
        throw runtime_error("Leaf node with name \""+nodename+"\" not found");
    }
    else {
        throw runtime_error("Material with name \""+matname+"\" not found");
    }
}

void ScenegraphImporter::parseAddChild(istream& input) {
    string childname,parentname;
    input >> childname >> parentname;
    //std::cout << "command: add-child" << " " << childname << " " << parentname << std::endl;

    // find parent node in array and cast to parentSGNode
    ParentSGNode * parentNode = NULL;
    SGNode * childNode = NULL;

    // if the child node is found in array, set childNode
    if (nodes.find(parentname)!=nodes.end()) {
        parentNode = dynamic_cast<ParentSGNode *>(nodes[parentname]);
    }
    // if the child node is found in array, set childNode
    if (nodes.find(childname)!=nodes.end()) {
        childNode = nodes[childname];
    }

    // if parent node and child node are not invalid, set parent of child node to be parent node
    if ((parentNode!=NULL) && (childNode!=NULL)) {
        parentNode->addChild(childNode);
    }
    else if (parentNode==NULL) {
        throw runtime_error("Parent node with name \""+parentname+"\" not found");
    }
    else {
        throw runtime_error("Child node with name \""+childname+"\" not found");
    }
}

void ScenegraphImporter::parseSetRoot(istream& input) {
    string rootname;
    input >> rootname;
    //std::cout << "command: assign-root " << rootname << std::endl;
    if (nodes.find(rootname)!=nodes.end()) {
        root = nodes[rootname];
    }
    else {
        throw runtime_error("Root node with name \""+rootname+"\" not found");
    }
    
}

// parseAddChild() and parseAssignMaterial() is implicitly tested
void ScenegraphImporter::testParse(IScenegraph* scenegraph) {
    std::cout << "----------------------" << std::endl;

    // test for parseMaterial
    std::cout << "materials size: " << materials.size() << std::endl;
    for (auto i : materials) {
        std::cout << "material: " << i.first << std::endl;
        std::cout << "   ambient: " << glm::to_string(i.second.getAmbient()) << std::endl;
        std::cout << "   diffuse: " << glm::to_string(i.second.getDiffuse()) << std::endl;
        std::cout << "   specular: " << glm::to_string(i.second.getSpecular()) << std::endl;
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "nodes size: " << nodes.size() << std::endl;

    // test for parseGroup
    std::cout << "   GROUP NODES:"<< std::endl;
     for (auto i : nodes) {
        string nodeName = typeid(*i.second).name();
        if (nodeName.find("GroupNode") != std::string::npos) {
            GroupNode* groupNode = dynamic_cast<GroupNode *> (i.second);
            std::cout << "      group node: " << groupNode->getName() << std::endl;
            vector<SGNode *> children = groupNode->getChildren();
            for (int i = 0; i < children.size(); i++) {
                std::cout << "         child: " << children[i]->getName() << " - " << typeid(*children[i]).name()<< std::endl;
            }
            std::cout << std::endl;
            }
    }

    std::cout << std::endl;

    // test for parseLeaf
    std::cout << "   LEAF NODES:"<< std::endl;
     for (auto i : nodes) {
        string nodeName = typeid(*i.second).name();
        if (nodeName.find("LeafNode") != std::string::npos) {
            LeafNode* leafNode = dynamic_cast<LeafNode *> (i.second);
            std::cout << "      leaf node: " << leafNode->getName() << std::endl;
            std::cout << "      instance of: " << leafNode->getInstanceOf() << std::endl;
            std::cout << "      material ambient: " << glm::to_string(leafNode->getMaterial().getAmbient()) << std::endl;
            std::cout << std::endl;
            }
    }

    std::cout << std::endl;

    // test for parseScale
    std::cout << "   SCALE NODES:"<< std::endl;
     for (auto i : nodes) {
        string nodeName = typeid(*i.second).name();
        if (nodeName.find("ScaleTransform") != std::string::npos) {
            ScaleTransform* scaleNode = dynamic_cast<ScaleTransform *> (i.second);
            std::cout << "      node name: " << scaleNode->getName() << std::endl;
            std::cout << "      scale values: " << glm::to_string(scaleNode->getScale()) << std::endl;
            vector<SGNode *> children = scaleNode->getChildren();
            for (int i = 0; i < children.size(); i++) {
                std::cout << "      child: " << children[i]->getName() << " - " << typeid(*children[i]).name()<< std::endl;
            }
            std::cout << std::endl;
            }
    }

    std::cout << std::endl;

    // test for parseRotate
    std::cout << "   ROTATE NODES:"<< std::endl;
     for (auto i : nodes) {
        string nodeName = typeid(*i.second).name();
        if (nodeName.find("RotateTransform") != std::string::npos) {
            RotateTransform* rotateNode = dynamic_cast<RotateTransform *> (i.second);
            std::cout << "      node name: " << rotateNode->getName() << std::endl;
            std::cout << "      rotation angle(radians): " << rotateNode->getAngleInRadians() << std::endl;
            std::cout << "      rotation axis: " << glm::to_string(rotateNode->getRotationAxis()) << std::endl;
            vector<SGNode *> children = rotateNode->getChildren();
            for (int i = 0; i < children.size(); i++) {
                std::cout << "      child: " << children[i]->getName() << " - " << typeid(*children[i]).name()<< std::endl;
            }
            std::cout << std::endl;
            }
    }

    std::cout << std::endl;
    
    // test for parseTranslate
    std::cout << "   TRANSLATE NODES:"<< std::endl;
     for (auto i : nodes) {
        string nodeName = typeid(*i.second).name();
        if (nodeName.find("TranslateTransform") != std::string::npos) {
            TranslateTransform* translateNode = dynamic_cast<TranslateTransform *> (i.second);
            std::cout << "      node name: " << translateNode->getName() << std::endl;
            std::cout << "      translation: " << glm::to_string(translateNode->getTranslate()) << std::endl;
            std::cout << std::endl;
            vector<SGNode *> children = translateNode->getChildren();
            for (int i = 0; i < children.size(); i++) {
                std::cout << "      child: " << children[i]->getName() << " - " << typeid(*children[i]).name()<< std::endl;
            }
            }
    }

    std::cout << std::endl;

    // tests for parseInstance
    std::cout << "meshPaths size: " << meshPaths.size() << std::endl;
    for (auto i : meshPaths) {
        std::cout << "mesh path: " << i.first << " - " << i.second << std::endl;
    }
    std::cout << "meshes size: " << meshes.size() << std::endl;
    for (auto i : meshes) {
        std::cout << "mesh: " << i.first << std::endl;
    }

    std::cout << std::endl;

    // testing Scenegraph construction
    SGNode *scenegraphRoot = scenegraph->getRoot(); // testing parseSetRoot()
    std::cout << "root name: " << scenegraphRoot->getName() << std::endl;
    map<string,util::PolygonMesh<VertexAttrib>> sgMeshes = scenegraph->getMeshes();
    std::cout << "Number of meshes IN SCENEGRAPH: " << sgMeshes.size() << std::endl;
    map<string,string> sgMeshPaths = scenegraph->getMeshPaths();
    std::cout << "Number of mesh paths IN SCENEGRAPH: " << sgMeshPaths.size() << std::endl;

    std::cout << "----------------------" << std::endl;

}