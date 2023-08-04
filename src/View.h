#ifndef __VIEW_H__
#define __VIEW_H__
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
using namespace std;

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include "PolygonMesh.h"
#include "VertexAttrib.h"
#include "Material.h"
#include "Object.h"
#include "ObjectInstance.h"
#include "Callbacks.h"

#include "sgraph/IScenegraph.h"
#include "sgraph/Scenegraph.h"
#include "sgraph/SGNodeVisitor.h"
#include "sgraph/GLScenegraphRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>


class View
{
    
public:
    View();
    ~View();

    /*
        to check for copy constructors
    */
    View (View &t) {
        std::cout << "VIEW COPY CONSTRUCTOR CALLED" << std::endl;
    }

    void init(Callbacks* callbacks,map<string,util::PolygonMesh<VertexAttrib>>& meshes);
    bool shouldWindowClose();
    void display(IScenegraph *scenegraph);
    void closeWindow();

private:
    GLFWwindow* window;
    util::ShaderProgram program;
    glm::mat4 projection;
    util::ShaderLocationsVault shaderLocations;
    int angleOfRotation;
    int frames;
    double time;
    stack<glm::mat4> modelview;
    map<string,util::ObjectInstance *> objects;
    SGNodeVisitor *renderer;

    void onkey(GLFWwindow* window, int key, int scancode, int action, int mods);
    void reshape(GLFWwindow* window, int width, int height);
    void error_callback(int error, const char* description);
    void dispose(GLFWwindow* window);
    void initObjects(map<string,util::PolygonMesh<VertexAttrib>>& meshes);
    
};

#endif