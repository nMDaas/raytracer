#include "ScenegraphImporter.h"

ScenegraphImporter::ScenegraphImporter() {
}

ScenegraphImporter::~ScenegraphImporter()
{
    
}

IScenegraph* ScenegraphImporter::parse(std::istream& input) {
    string inputWithOutCommentsString = stripComments(input); // remove comments
    istringstream inputWithOutComments(inputWithOutCommentsString);
    string command;
    while (inputWithOutComments >> command) {
        if (command == "instance") {
            std::cout << "instance" << std::endl;
        }
        else if (command == "group") {
            std::cout << "group" << std::endl;
        }
        else if (command == "leaf") {
            std::cout << "leaf" << std::endl;
        }
        else if (command == "material") {
            std::cout << "material" << std::endl;
        }
        else if (command == "scale") {
            std::cout << "scale" << std::endl;
        }
        else if (command == "rotate") {
            std::cout << "rotate" << std::endl;
        }
        else if (command == "translate") {
            std::cout << "translate" << std::endl;
        }
        else if (command == "copy") {
            std::cout << "copy" << std::endl;
        }
        else if (command == "import") {
            std::cout << "import" << std::endl;
        }
        else if (command == "assign-material") {
            std::cout << "assign-material" << std::endl;
        }
        else if (command == "add-child") {
            std::cout << "add-child" << std::endl;
        }
        else if (command == "assign-root") {
            std::cout << "assign-root" << std::endl;
        }
        else {
            std::cout << "other command: " << command << std::endl;
        }
    }

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