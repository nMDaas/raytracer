#ifndef _SCENEGRAPHIMPORTER_H_
#define _SCENEGRAPHIMPORTER_H_
#include <iostream>
#include <istream>
#include <string>
#include <sstream>
using namespace std;

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

};

#endif