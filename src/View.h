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
#include "objects/MeshObject.h"

#include "sgraph/IScenegraph.h"
#include "sgraph/Scenegraph.h"
#include "sgraph/SGNodeVisitor.h"
#include "sgraph/GLScenegraphRenderer.h"
#include "sgraph/RaytracerRenderer.h"
#include "sgraph/AbstractRenderer.h"

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

    // to check for copy constructors
    View (View &t);

    void init(Callbacks* callbacks,map<string,util::PolygonMesh<VertexAttrib>>& meshes, map<string,MeshObject>& in_meshObjects, bool debugger, glm::vec3 camPos, glm::vec3 camTarget);
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
    stack<glm::mat4> reflection_modelview;
    stack<glm::mat4> transparency_modelview;
    map<string,util::ObjectInstance *> objects;
    map<string,MeshObject> meshObjects;
    SGNodeVisitor *renderer;
    SGNodeVisitor *raytracerRenderer;
    SGNodeVisitor *reflectionVisitor;
    SGNodeVisitor *transparencyVisitor;
    vector<LightLocation> lightLocations; // shader locations for lights
    int WIDTH = 600; // width of ppm file, in pixels (width:height::29:40)
    int HEIGHT = 600; // height of ppm file, in pixels
    float cameraFOV = (float) glm::radians(60.0f);
    stack<float> refractiveIndexStack; 

    // camera details - assumes that we are looking down the z axis
    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;

    void reshape(GLFWwindow* window, int width, int height);
    void error_callback(int error, const char* description);
    void dispose(GLFWwindow* window);
    void initObjects(map<string,util::PolygonMesh<VertexAttrib>>& meshes);
    void initShaderVariables(vector<util::Light>& lights);
    glm::vec4 getColor(HitRecord hitRecord, vector<vector<util::Light>> sceneLightCollections, IScenegraph* scenegraph, glm::vec4 rayDirection, int reflectiveBounces, int refractiveBounces); // RGB values are between 0 and 1
    glm::vec4 getAbsorptionColor(HitRecord hitRecord, vector<vector<util::Light>> sceneLightCollections, IScenegraph* scenegraph); 
    glm::vec4 getReflectionColor(HitRecord hitRecord, vector<vector<util::Light>> sceneLightCollections, IScenegraph* scenegraph, glm::vec4 rayDirection, int reflectiveBounces, int refractiveBounces);
    glm::vec4 getTransparencyColor(HitRecord hitRecord, vector<vector<util::Light>> sceneLightCollections, IScenegraph* scenegraph, glm::vec4 rayDirection, int reflectiveBounces, int refractiveBounces);
    int clipValue(int val);
    bool inShadow(HitRecord hitRecord, util::Light light, IScenegraph* scenegraph);
    float getShadowIntensity(HitRecord hitRecord, vector<util::Light> lightCollection, IScenegraph* scenegraph);
    glm::highp_mat4 getLookAtMatrix();
};

#endif