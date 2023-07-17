#include "ScenegraphImporter.h"

ScenegraphImporter::ScenegraphImporter() {
    std::cout << "testing this class" << std::endl;
}

ScenegraphImporter::~ScenegraphImporter()
{
    
}

IScenegraph ScenegraphImporter::*parse(std::istream& input) {
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