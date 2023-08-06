#include "View.h"

View::View() {

}

View::~View(){

}

bool View::shouldWindowClose() {
    return glfwWindowShouldClose(window);
}

void View::closeWindow() {
    for (map<string,util::ObjectInstance *>::iterator it=objects.begin();
           it!=objects.end();
           it++) {
          it->second->cleanup();
          delete it->second;
    } 
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

void View::initObjects(map<string,util::PolygonMesh<VertexAttrib>>& meshes) {
    /*
        In the mesh we have attributes for each vertex. In the shader, 
        we have variables for each vertex attribute. We need to create a 
        connection between attribute name in the mesh and corresponding
        shader variable name.
    */
    map<string, string> shaderVarsToVertexAttribs;
    // currently there are only two per-vertex attribute: position and color
    shaderVarsToVertexAttribs["vPosition"] = "position";
    shaderVarsToVertexAttribs["vNormal"] = "normal";

    // meshes needs to be iterated like this because it is a map
    // create an ObjectInstance for each mesh by passing in the name and polygon mesh (stored in meshes map)
    for (typename map<string,util::PolygonMesh<VertexAttrib> >::iterator it=meshes.begin();
           it!=meshes.end();
           it++) {
        util::ObjectInstance * obj = new util::ObjectInstance(it->first);
        obj->initPolygonMesh(shaderLocations,shaderVarsToVertexAttribs,it->second);
        objects[it->first] = obj; // ObjectInstance stored in map
    }
}

void View::init(Callbacks* callbacks,map<string,util::PolygonMesh<VertexAttrib>>& meshes) {

    // This function initializes the GLFW library because before GLFW functions can be used, GLFW must be initialized
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // ... 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Setup window and terminate the program if this is not successful
    window = glfwCreateWindow(800,800, "Raytracer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowUserPointer(window, (void *)callbacks); // set pointer of window to this

    //using C++ functions as callbacks to a C-style library
    // callback to onkey() method
    glfwSetKeyCallback(window, 
    [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        static_cast<View*>(glfwGetWindowUserPointer(window))->onkey(window,key,scancode,action,mods);
    });

    // callback to reshape() method
    glfwSetWindowSizeCallback(window, 
    [](GLFWwindow* window, int width,int height)
    {
        static_cast<View*>(glfwGetWindowUserPointer(window))->reshape(window,width,height);
    });

    // ...
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // debugger - create shader program with a vertex and fragment shader 
    // program.createProgram(string("shaders/phong-multiple.vert"),
    //                    string("shaders/phong-multiple.frag"));

    // terminal - create shader program with a vertex and fragment shader 
     program.createProgram(string("src/shaders/phong-multiple.vert"),
                          string("src/shaders/phong-multiple.frag"));
    //program.enable(); // set this program to be in use
    shaderLocations = program.getAllShaderVariables();

    initObjects(meshes);

    int window_width,window_height;
    // gets the size of framebuffer of the window and stores it in 2nd and 3rd parameter
    // removes need to store window dimensions separately
    glfwGetFramebufferSize(window,&window_width,&window_height); 

    // CAN UNCOMMENT THIS IF YOU WANT ORTHOGRAPHIC INSTEAD OF PERSPECTIVE PROJECTION
    // projection = glm::ortho(-400.0f,400.0f,-400.0f,400.0f,0.1f,10000.0f);

    // perspective projection - makes objects farther away appear smaller 
    // 60 degrees is how much you can see (if you don't move your head)
    // next parameter: aspect vision - aspect ratio of dimension to make sure window doesn't distort
    projection = glm::perspective((float)glm::radians(60.0f),
            (float) window_width/window_height,
            0.1f, // near distance
            10000.0f); // far distance

    //prepare the projection matrix for orthographic projection
	glViewport(0, 0, window_width, window_height);

    renderer = new GLScenegraphRenderer(modelview, objects, shaderLocations);

    frames = 0;
    time = glfwGetTime();
}

void View::initShaderVariables(vector<util::Light>& lights) {
    for (int i = 0; i < lights.size(); i++) {
    LightLocation ll;
    stringstream name;

    name << "light[" << i << "]";
    ll.ambient = shaderLocations.getLocation(name.str() + ".ambient");
    ll.diffuse = shaderLocations.getLocation(name.str() + ".diffuse");
    ll.specular = shaderLocations.getLocation(name.str() + ".specular");
    ll.position = shaderLocations.getLocation(name.str() + ".position");
    lightLocations.push_back(ll);
    }
}

void View::display(IScenegraph *scenegraph) {
    program.enable();
    glClearColor(0, 0, 0, 1); // set background color to black

    //clear the background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    //send projection matrix to GPU    
    glUniformMatrix4fv(shaderLocations.getLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    while (!modelview.empty()) {
        modelview.pop();
    }

    modelview.push(glm::mat4(1.0));

    modelview.top() = modelview.top() * glm::lookAt(glm::vec3(0.0f,0.0f,150.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
      
    //draw scene graph here
    scenegraph->getRoot()->accept(renderer);
    
    vector<util::Light> sceneLights = renderer->getLights();

    initShaderVariables(sceneLights);

    for (int i = 0; i < sceneLights.size(); i++) {
        //glm::vec4 pos = modelview.top() * sceneLights[i].getPosition();
        glm::vec4 pos = sceneLights[i].getPosition();
        std::cout << "LIGHT POS: " << glm::to_string(pos) << std::endl;
        glUniform4fv(lightLocations[i].position, 1, glm::value_ptr(pos));
    }

    //pass light color properties to shader
    glUniform1i(shaderLocations.getLocation("numLights"),sceneLights.size());

    //pass light colors to the shader
    for (int i = 0; i < sceneLights.size(); i++) {
        //std::cout << "light ambient: " << glm::to_string(sceneLights[i].getAmbient()) << std::endl;
        glUniform3fv(lightLocations[i].ambient, 1, glm::value_ptr(sceneLights[i].getAmbient()));
        //glm::vec4 pos = sceneLights[i].getPosition();
        //glUniform4fv(lightLocations[i].position, 1, glm::value_ptr(pos));
        //std::cout << "light diffuse: " << glm::to_string(sceneLights[i].getDiffuse()) << std::endl;
        glUniform3fv(lightLocations[i].diffuse, 1, glm::value_ptr(sceneLights[i].getDiffuse()));
        glUniform3fv(lightLocations[i].specular, 1,glm::value_ptr(sceneLights[i].getSpecular()));
    }

    std::cout << "-------------" << std::endl;
    renderer->clearLights();

    modelview.pop();
    glFlush();
    program.disable();

    glfwSwapBuffers(window);
    glfwPollEvents();
    frames++;
    double currenttime = glfwGetTime();
    if ((currenttime-time)>1.0) {
        printf("Framerate: %2.0f\r",frames/(currenttime-time));
        frames = 0;
        time = currenttime;
    }
}

void View::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void View::dispose(GLFWwindow* window)
{
    closeWindow();
}