#include "View.h"

View::View() {

}

View::~View(){

}

bool View::shouldWindowClose() {
    return glfwWindowShouldClose(window);
}

void View::closeWindow() {
    for (int i=0;i<objects.size();i++) {
        objects[i].object.cleanup();
       // delete objects[i].object;
    }
    objects.clear();
    glfwDestroyWindow(window);

    glfwTerminate();
}

void View::onkey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void View::reshape(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);

    // last few point is for the z axis (something very close to something very far)
    projection = glm::ortho(-400.0f,400.0f,-400.0f,400.0f,0.1f,10000.0f);
}

void View::init(vector<util::PolygonMesh<VertexAttrib>>& meshes,vector<util::Material>& materials) {

    // This function initializes the GLFW library because before GLFW functions can be used, GLFW must be initialized
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // ... 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Setup window and terminate the program if this is not successful
    window_dimensions = glm::vec2(800,800);
    window = glfwCreateWindow(window_dimensions.x,window_dimensions.y, "Raytracer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowUserPointer(window, this); // set pointer of window to this

    //using C++ functions as callbacks to a C-style library
    glfwSetKeyCallback(window, 
    [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        static_cast<View*>(glfwGetWindowUserPointer(window))->onkey(window,key,scancode,action,mods);
    });

    glfwSetWindowSizeCallback(window, 
    [](GLFWwindow* window, int width,int height)
    {
        static_cast<View*>(glfwGetWindowUserPointer(window))->reshape(window,width,height);
    });

    // ...
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // create shader program with a vertex and fragment shader
    program.createProgram(string("shaders/default.vert"),
                          string("shaders/default.frag"));
    program.enable(); // set this program to be in use
    shaderLocations = program.getAllShaderVariables();
  
    /*
        In the mesh we have attributes for each vertex. In the shader, 
        we have variables for each vertex attribute. We need to create a 
        connection between attribute name in the mesh and corresponding
        shader variable name.
    */
    map<string, string> shaderVarsToVertexAttribs;
    // currently there are only two per-vertex attribute: position and color
    shaderVarsToVertexAttribs["vPosition"] = "position";

    for (int i=0;i<meshes.size();i++) {
        util::ObjectInstance obj("triangles");
        obj.initPolygonMesh<VertexAttrib>(
            program,                    // the shader program
            shaderLocations,            // the shader locations
            shaderVarsToVertexAttribs,  // the shader variable -> attrib map
            meshes[i]);                 // the actual mesh object
        Object objStruct;
        objStruct.object = obj;
        objStruct.material = materials[i];
        objects.push_back(objStruct);

    }

    //prepare the projection matrix for orthographic projection
	glViewport(0, 0, window_dimensions.x, window_dimensions.y);

    // CAN UNCOMMENT THIS IF YOU WANT ORTHOGRAPHIC INSTEAD OF PERSPECTIVE PROJECTION
    // projection = glm::ortho(-400.0f,400.0f,-400.0f,400.0f,0.1f,10000.0f);

    // perspective projection - makes objects farther away appear smaller 
    // 60 degrees is how much you can see (if you don't move your head)
    // next parameter: aspect vision - aspect ratio of dimension to make sure window doesn't distort
    projection = glm::perspective((float)glm::radians(60.0f),
            (float) window_dimensions.x/window_dimensions.y,
            0.1f, // near distance
            10000.0f); // far distance

    angleOfRotation = 0;
    frames = 0;
    time = glfwGetTime();
}

void View::display() {
    
}