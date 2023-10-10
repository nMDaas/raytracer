#include "ObjImporter.h"

ObjImporter::ObjImporter() {}

ObjImporter::~ObjImporter() {}

// to check for copy constructors
ObjImporter::ObjImporter (ObjImporter &t) {
    std::cout << "OBJ IMPORTER COPY CONSTRUCTOR CALLED" << std::endl;
}

void ObjImporter::parseObjFile(std::istream& input) {
    string inputWithOutCommentsString = stripComments(input); // remove comments
    istringstream inputWithOutComments(inputWithOutCommentsString);
    string command;
    while (inputWithOutComments >> command) {
        if (command == "v") {
            parseVertex(inputWithOutComments);
        }
        else if (command == "f") {
            parseFace(inputWithOutComments);
        }
    }
}

std::string ObjImporter::stripComments(std::istream& input) {
    std::string line;
    stringstream clean;
    vertices.push_back(glm::vec4(0.0f,0.0f,0.0f,0.0f)); // dummy first vertex so vertices start from 1
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

void ObjImporter::parseVertex(istream& input) {
    float x,y,z;
    input >> x >> y >> z;
    vertices.push_back(glm::vec4(x,y,z,1.0f));
}

void ObjImporter::parseFace(std::istream& input) {
    string v1,v2,v3;
    input >> v1 >> v2 >> v3;
    std::cout << "v1[0]: " << v1[0] << std::endl;
    int v1int = ((int) v1[0]) - 48;
    int v2int = ((int) v2[0]) - 48;
    int v3int = ((int) v3[0]) - 48;
    //std::cout << "v1int: " << v1int << std::endl;
    //std::cout << "vertices{v1[0]}: " << glm::to_string(vertices[v1int]) << std::endl;
    //std::cout << vertices[(int) v1[0]] << " " << vertices[(int) v2[0]] << " " << vertices[(int) v3[0]] << std::endl;
    Triangle triangle(vertices[v1int],vertices[v2int],vertices[v3int]);
    triangles.push_back(triangle);
}

void ObjImporter::testParse(){
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << "vertex: " << glm::to_string(vertices[i]) << std::endl;
    }

    std::cout << "Triangles: " << std::endl;

    for (int i = 0; i < triangles.size(); i++) {
        triangles[i].printTriangleDetails();
    } 
}