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
#include "LightLocation.h"

#include "sgraph/IScenegraph.h"
#include "sgraph/Scenegraph.h"
#include "sgraph/SGNodeVisitor.h"
#include "sgraph/GLScenegraphRenderer.h"
#include "sgraph/RaytracerRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>
#include <glm/gtx/string_cast.hpp>


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

    void init(Callbacks* callbacks,map<string,util::PolygonMesh<VertexAttrib>>& meshes, bool debugger);
    void raytrace(bool debugging,IScenegraph *scenegraph);
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
    stack<glm::mat4> raytracer_modelview;
    map<string,util::ObjectInstance *> objects;
    SGNodeVisitor *renderer;
    SGNodeVisitor *raytracerRenderer;
    vector<LightLocation> lightLocations; // shader locations for lights
    int WIDTH = 300; // width of ppm file, in pixels
    int HEIGHT = 300; // height of ppm file, in pixels
    float cameraFOV = (float) glm::radians(60.0f);

    void reshape(GLFWwindow* window, int width, int height);
    void error_callback(int error, const char* description);
    void dispose(GLFWwindow* window);
    void initObjects(map<string,util::PolygonMesh<VertexAttrib>>& meshes);
    void initShaderVariables(vector<util::Light>& lights);
    
    glm::vec3 getColor(HitRecord hitRecord, vector<util::Light> sceneLights);
    int clipValue(int val);
};

#endif