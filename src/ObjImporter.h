#ifndef _OBJIMPORTER_H_
#define _OBJIMPORTER_H_

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class ObjImporter {
    public:
        ObjImporter();
        ~ObjImporter();

        // to check for copy constructors
        ObjImporter (ObjImporter &t);

        void parseObjFile(std::istream& input);

    private: 
        std::string stripComments(std::istream& input);
};

#endif