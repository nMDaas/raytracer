#include "ScenegraphImporter.h"

#include <ImageLoader.h>
#include <PPMImageLoader.h>

ScenegraphImporter::ScenegraphImporter(bool debugger) {
    root = NULL;
    ImageLoader *loader = new PPMImageLoader();
    if (debugger) {
        loader->load("textures/white.ppm");
    }
    else {
        loader->load("src/textures/white.ppm");
    }

    string name = "default";
    TextureImage* texture = new TextureImage(loader->getPixels(), loader->getWidth(), loader->getHeight(), name);
    textureObjects[name] = texture;
}

ScenegraphImporter::~ScenegraphImporter()
{
    
}

ScenegraphImporter::ScenegraphImporter (ScenegraphImporter &t) {
    std::cout << "SCENEGRAPH IMPORTER COPY CONSTRUCTOR CALLED" << std::endl;
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
        else if (command == "light") {
            parseLight(inputWithOutComments);
        }
        else if (command == "spotlight") {
            parseSpotlight(inputWithOutComments);
        }
        else if (command == "material") {
            parseMaterial(inputWithOutComments);
        }
        else if (command == "texture") {
            parseTexture(inputWithOutComments);
        }
        else if (command == "assign-texture") {
            parseAssignTexture(inputWithOutComments);
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
        else if (command == "camera") {
            parseCamera(inputWithOutComments);
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
        scenegraph->setMeshObjects(meshObjects);
        scenegraph->setCameraPos(cameraPos);
        scenegraph->setCameraTarget(cameraTarget);
        return scenegraph;
    }
    else {
        throw runtime_error("Parsed scene graph, but nothing set as root");
    }

}

void ScenegraphImporter::addInstance(string name, string path) {
    meshPaths[name] = path;
    ifstream in(path);
    if (in.is_open()) {
        util::PolygonMesh<VertexAttrib> mesh = util::ObjImporter<VertexAttrib>::importFile(in,false);
        meshes[name] = mesh;         
    } 
}

void ScenegraphImporter::parseInstance(istream& input) {
    string name,path;
    input >> name >> path;
    meshPaths[name] = path;

    if (name == "box" || name == "sphere" || name == "cylinder" || name == "cone") {
        // add instance only if path is valid
        std::ifstream test(path); 
        if (test)
        {
            ifstream in(path);
            if (in.is_open()) {
                util::PolygonMesh<VertexAttrib> mesh = util::ObjImporter<VertexAttrib>::importFile(in,false);
                meshes[name] = mesh;         
            } 
        }
    }
    else {
        std::ifstream test(path); 
        if (!test)
        {
            throw runtime_error("The file doesn't exist");
        }

        ifstream inFile(path);
        parseObjFile(inFile,name);
    }
    
}

void ScenegraphImporter::parseGroup(istream& input) {
    string name;
    input >> name;
    SGNode *group = new GroupNode(name,NULL);
    nodes[name] = group;
}

void ScenegraphImporter::parseLeaf(istream& input) {
    string name,command,instanceof;
    input >> name >> command;
    if (command == "instanceof") {
        input >> instanceof;
    }
    SGNode *leaf = new LeafNode(instanceof,name,NULL);
    auto search = textureObjects.find("default");
    TextureImage* textureImage = search->second;
    dynamic_cast<LeafNode *>(leaf)->setTexture(textureImage);
    nodes[name] = leaf;
}

void ScenegraphImporter::parseLight(istream& input) {
    string name;
    input >> name;
    float ambientR,ambientG,ambientB;
    input >> ambientR >> ambientG >> ambientB;
    float diffuseR,diffuseG,diffuseB;
    input >> diffuseR >> diffuseG >> diffuseB;
    float specularR,specularG,specularB;
    input >> specularR >> specularG >> specularB;

    SGNode *light = new LightNode(name,NULL,glm::vec3(ambientR,ambientG,ambientB),
        glm::vec3(diffuseR,diffuseG,diffuseB),glm::vec3(specularR,specularG,specularB));
    nodes[name] = light;
}

void ScenegraphImporter::parseSpotlight(istream& input) {
    string name;
    input >> name;
    float ambientR,ambientG,ambientB;
    input >> ambientR >> ambientG >> ambientB;
    float diffuseR,diffuseG,diffuseB;
    input >> diffuseR >> diffuseG >> diffuseB;
    float specularR,specularG,specularB;
    input >> specularR >> specularG >> specularB;
    float dx,dy,dz;
    input >> dx >> dy >> dz;
    float spotAngle;
    input >> spotAngle;

    SGNode *spotlight = new SpotlightNode(name,NULL,glm::vec3(ambientR,ambientG,ambientB),
        glm::vec3(diffuseR,diffuseG,diffuseB),glm::vec3(specularR,specularG,specularB),glm::vec4(dx,dy,dz,0),spotAngle);
    nodes[name] = spotlight;
}

void ScenegraphImporter::parseMaterial(istream& input) {
    util::Material mat;
    float r,g,b;
    float absorption,reflection,transparency;
    float refractiveIndex;
    string name;
    input >> name;
    string command;
    input >> command;
    while (command!="end-material") {
        if (command == "ambient") {
            input >> r >> g >> b;
            mat.setAmbient(r,g,b);
        }
        else if (command == "diffuse") {
            input >> r >> g >> b;
            mat.setDiffuse(r,g,b);
        }
        else if (command == "specular") {
            input >> r >> g >> b;
            mat.setSpecular(r,g,b);
        }
        else if (command == "emission") {
            input >> r >> g >> b;
            mat.setEmission(r,g,b);
        }
        else if (command == "shininess") {
            input >> r;
            mat.setShininess(r);
        }
        else if (command == "absorption") {
            input >> absorption;
            mat.setAbsorption(absorption);
        }
        else if (command == "reflection") {
            input >> reflection;
            mat.setReflection(reflection);
        }
        else if (command == "transparency") {
            input >> transparency;
            mat.setTransparency(transparency);
        }
        else if (command == "refractiveIndex") {
            input >> refractiveIndex;
            mat.setRefractiveIndex(refractiveIndex);
        }
        input >> command;
    }
     materials[name] = mat;
}

void ScenegraphImporter::parseScale(istream& input) {
    string name;
    input >> name;
    float sx,sy,sz;
    input >> sx >> sy >> sz;
    SGNode *scaleNode = new ScaleTransform(sx,sy,sz,name,NULL);
    nodes[name] = scaleNode;
}

void ScenegraphImporter::parseRotate(istream& input) {
    string name;
    input >> name;
    float angleInDegrees,ax,ay,az;
    input >> angleInDegrees >> ax >> ay >> az;
    SGNode *rotateNode = new RotateTransform(glm::radians(angleInDegrees),ax,ay,az,name,NULL);
    nodes[name] = rotateNode;  
}

void ScenegraphImporter::parseTranslate(istream& input) {
    string name;
    input >> name;
    float tx,ty,tz;
    input >> tx >> ty >> tz;
    SGNode *translateNode = new TranslateTransform(tx,ty,tz,name,NULL);
    nodes[name] = translateNode;  
}

void ScenegraphImporter::parseCopy(istream& input) {
    string nodename,copyof;
    input >> nodename >> copyof;
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
    ifstream external_scenegraph_file(filepath);
    if (external_scenegraph_file.is_open()) {
        IScenegraph *importedSG = parse(external_scenegraph_file);
        nodes[nodename] = importedSG->getRoot();
        importedSG->makeScenegraph(NULL);
        delete importedSG;
    }
}

void ScenegraphImporter::parseAssignMaterial(istream& input) {
    string nodename,matname;
    input >> nodename >> matname;
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
    if (nodes.find(rootname)!=nodes.end()) {
        root = nodes[rootname];
    }
    else {
        throw runtime_error("Root node with name \""+rootname+"\" not found");
    }
    
}

void ScenegraphImporter::parseTexture(istream& input) {
    string name,filename;
    input >> name >> filename;

    std::ifstream test(filename); 
    if (!test)
    {
        throw runtime_error("Texture file " + filename + " does not exist.");
    }

    ImageLoader *loader = new PPMImageLoader();
    loader->load(filename);
    TextureImage* texture = new TextureImage(loader->getPixels(), loader->getWidth(), loader->getHeight(), name);
    textureObjects[name] = texture;
}

void ScenegraphImporter::parseAssignTexture(istream& input) {
    string nodename,texturename;
    input >> nodename >> texturename;
    LeafNode *leafNode = dynamic_cast<LeafNode *>(nodes[nodename]);
    if ((leafNode!=NULL) && (textureObjects.find(texturename)!=textureObjects.end())) {
        auto search = textureObjects.find(texturename);
        TextureImage* textureImage = search->second;
        leafNode->setTexture(textureImage);
    }
}

void ScenegraphImporter::parseCamera(istream& input) {
    float px,py,pz,tx,ty,tz;
    input >> px >> py >> pz >> tx >> ty >> tz;
    cameraPos = glm::vec3(px,py,pz);
    cameraTarget = glm::vec3(tx,ty,tz);
}

void ScenegraphImporter::parseObjFile(std::istream& input, string meshObjectName) {
    string inputWithOutCommentsString = stripComments(input); // remove comments
    istringstream inputWithOutComments(inputWithOutCommentsString);
    string command;
    MeshObject meshObject;
    while (inputWithOutComments >> command) {
        if (command == "v") {
            parseVertex(inputWithOutComments);
        }
        else if (command == "f") {
            parseFace(inputWithOutComments);
        }
    }
    meshObject.setTriangles(&triangles);
    meshObjects[meshObjectName] = meshObject;
    vertices.clear();
    triangles.clear();
}

void ScenegraphImporter::parseVertex(istream& input) {
    float x,y,z;
    input >> x >> y >> z;
    vertices.push_back(glm::vec4(x,y,z,1.0f));
}

void ScenegraphImporter::parseFace(std::istream& input) {
    string v1,v2,v3;
    input >> v1 >> v2 >> v3;
    int v1int = ((int) v1[0]) - 48;
    int v2int = ((int) v2[0]) - 48;
    int v3int = ((int) v3[0]) - 48;
    Triangle triangle(vertices[v1int],vertices[v2int],vertices[v3int]);
    triangles.push_back(triangle);
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
        std::cout << "   absorption: " << i.second.getAbsorption() << std::endl;
        std::cout << "   reflection: " << i.second.getReflection() << std::endl;
        std::cout << "   transparency: " << i.second.getTransparency() << std::endl;
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
            std::cout << "      material ambient: " << glm::to_string(leafNode->getMaterial()->getAmbient()) << std::endl;
            std::cout << "      material diffuse: " << glm::to_string(leafNode->getMaterial()->getDiffuse()) << std::endl;
            std::cout << "      material specular: " << glm::to_string(leafNode->getMaterial()->getSpecular()) << std::endl;
            std::cout << "      texture: " << leafNode->getTexture()->getName() << std::endl;
            std::cout << std::endl;
            }
    }

    std::cout << std::endl;

    // test for parseLight
    std::cout << "   LIGHT NODES:"<< std::endl;
     for (auto i : nodes) {
        string nodeName = typeid(*i.second).name();
        if (nodeName.find("LightNode") != std::string::npos) {
            LightNode* lightNode = dynamic_cast<LightNode *> (i.second);
            std::vector<util::Light*>* nodeLightCellsP = lightNode->getLightCells();
            std::vector<util::Light*> nodeLightCells = *nodeLightCellsP;
            for (int i=0; i < nodeLightCellsP->size(); i++) {
                std::cout << "      light position " << i << ": " << glm::to_string(nodeLightCells[i]->getPosition()) << std::endl;
            }
            std::cout << "      light ambient: " << glm::to_string(lightNode->getLight()->getAmbient()) << std::endl;
            std::cout << "      light diffuse: " << glm::to_string(lightNode->getLight()->getDiffuse()) << std::endl;
            std::cout << "      light specular: " << glm::to_string(lightNode->getLight()->getSpecular()) << std::endl;
            std::cout << std::endl;
            }
    }

    std::cout << std::endl;

    // test for parseSpotlight
    std::cout << "   SPOTLIGHT NODES:"<< std::endl;
     for (auto i : nodes) {
        string nodeName = typeid(*i.second).name();
        if (nodeName.find("SpotlightNode") != std::string::npos) {
            SpotlightNode* spotlightNode = dynamic_cast<SpotlightNode *> (i.second);
            std::cout << "      spotlight node: " << spotlightNode->getName() << std::endl;
            std::cout << "      spotlight ambient: " << glm::to_string(spotlightNode->getLight()->getAmbient()) << std::endl;
            std::cout << "      spotlight diffuse: " << glm::to_string(spotlightNode->getLight()->getDiffuse()) << std::endl;
            std::cout << "      spotlight specular: " << glm::to_string(spotlightNode->getLight()->getSpecular()) << std::endl;
            std::cout << "      spotlight direction: " << glm::to_string(spotlightNode->getLight()->getSpotDirection()) << std::endl;
            std::cout << "      spotlight spot angle: " << spotlightNode->getLight()->getSpotCutoff() << std::endl;
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
    std::cout << "meshObjects size: " << meshObjects.size() << std::endl;

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