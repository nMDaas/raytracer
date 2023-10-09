#include "ObjImporter.h"

ObjImporter::ObjImporter() {}

ObjImporter::~ObjImporter() {}

// to check for copy constructors
ObjImporter::ObjImporter (ObjImporter &t) {
    std::cout << "OBJ IMPORTER COPY CONSTRUCTOR CALLED" << std::endl;
}