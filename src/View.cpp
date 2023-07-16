#include "View.h"

View::View() {

}

View::~View(){

}

void View::init(vector<util::PolygonMesh<VertexAttrib>>& meshes,vector<util::Material>& materials) {
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window_dimensions = glm::vec2(800,800);

    window = glfwCreateWindow(window_dimensions.x,window_dimensions.y, "ObjViewer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
     glfwSetWindowUserPointer(window, this);

  
}