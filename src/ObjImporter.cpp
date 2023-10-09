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
        std::cout << command << " "; 
    }
}

std::string ObjImporter::stripComments(std::istream& input) {
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