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
            std::cout << "other command: " << command << std::endl;
        }
    }

}

void ScenegraphImporter::parseInstance(istream& input) {
    std::cout << "instance" << std::endl;
}

void ScenegraphImporter::parseGroup(istream& input) {
    std::cout << "group" << std::endl;
}

void ScenegraphImporter::parseLeaf(istream& input) {
    std::cout << "leaf" << std::endl;
}

void ScenegraphImporter::parseMaterial(istream& input) {
    std::cout << "material" << std::endl;
}

void ScenegraphImporter::parseScale(istream& input) {
    std::cout << "scale" << std::endl;
}

void ScenegraphImporter::parseRotate(istream& input) {
    std::cout << "rotate" << std::endl;
}

void ScenegraphImporter::parseTranslate(istream& input) {
    std::cout << "translate" << std::endl;
}

void ScenegraphImporter::parseCopy(istream& input) {
    std::cout << "copy" << std::endl;
}

void ScenegraphImporter::parseImport(istream& input) {
    std::cout << "import" << std::endl;
}

void ScenegraphImporter::parseAssignMaterial(istream& input) {
    std::cout << "assign-material" << std::endl;
}

void ScenegraphImporter::parseAddChild(istream& input) {
    std::cout << "add-child" << std::endl;
}

void ScenegraphImporter::parseSetRoot(istream& input) {
    std::cout << "assign-root" << std::endl;
}