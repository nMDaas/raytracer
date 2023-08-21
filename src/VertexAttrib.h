#ifndef _VERTEXATTRIB_H_
#define _VERTEXATTRIB_H_

#include <glm/glm.hpp>
#include "IVertexData.h"
#include <sstream>



/*
 * This class represents the attributes of a single vertex. It is useful in building
 * PolygonMesh objects for many examples.
 *
 * It implements the IVertexData interface so that it can be converted into an array
 * of floats, to work with OpenGL buffers
 */
class VertexAttrib:public util::IVertexData
{


public:
    VertexAttrib();

    ~VertexAttrib();

    bool hasData(string attribName);

    vector<float> getData(string attribName);

    void setData(string attribName, const vector<float>& data);

    vector<string> getAllAttributes();

private:
    glm::vec4 position;
    glm::vec4 normal;
    glm::vec4 texcoord;
};

#endif
