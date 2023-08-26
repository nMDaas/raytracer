#ifndef _TEXTUREIMAGE_H_
#define _TEXTUREIMAGE_H_

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <string>

  /**
         A class that represents an image. Provides a function for bilinear interpolation
         */
  class TextureImage
  {

  public:
	  TextureImage();

    TextureImage(GLubyte* image,int width,int height,std::string name);

    ~TextureImage();

    GLubyte *getImage();

    int getWidth();

    int getHeight();

    std::string getName();

    glm::vec4 getColor(float x,float y);

  private:
    glm::vec3 getColor(int x,int y);
    void deleteImage();

    GLubyte *image;
    int width,height;
    std::string name;

  };
#endif
