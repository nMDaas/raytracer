#ifndef _OBJIMPORTER_H_
#define _OBJIMPORTER_H_

#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>
#include <glm/gtx/string_cast.hpp>

#include "objects/Triangle.h"
#include "objects/MeshObject.h"

/* to import non primitive objects that are made of triangles */
class ObjImporter {
    public:
        ObjImporter();
        ~ObjImporter();

        // to check for copy constructors
        ObjImporter (ObjImporter &t);

        void parseObjFile(std::istream& input);
        void testParse();
        MeshObject* getMeshObject();

    private: 
        std::string stripComments(std::istream& input);
        void parseVertex(std::istream& input);
        void parseFace(std::istream& input);

        std::vector<glm::vec4> vertices;

        MeshObject meshObject;
};

#endif