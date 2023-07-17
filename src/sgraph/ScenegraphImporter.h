#ifndef _SCENEGRAPHIMPORTER_H_
#define _SCENEGRAPHIMPORTER_H_
#include <iostream>

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

        private: 

};

#endif