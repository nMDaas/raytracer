#ifndef __VIEW_H__
#define __VIEW_H__
#include <iostream>

#include "PolygonMesh.h"
#include "VertexAttrib.h"
#include "Material.h"
#include "Object.h"
#include "ObjectInstance.h"

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

    void init(vector<util::PolygonMesh<VertexAttrib>>& meshes,vector<util::Material>& materials);

private:
    glm::vec2 window_dimensions;
    GLFWwindow* window;
    util::ShaderProgram program;
    glm::mat4 projection;
    util::ShaderLocationsVault shaderLocations;
    vector<Object> objects;

    void onkey(GLFWwindow* window, int key, int scancode, int action, int mods);
    void reshape(GLFWwindow* window, int width, int height);
    
};

#endif