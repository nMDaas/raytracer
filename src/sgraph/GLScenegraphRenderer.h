#ifndef _GLSCENEGRAPHRENDERER_H_
#define _GLSCENEGRAPHRENDERER_H_
#include <stack>
#include <map>

#include <glm/gtx/string_cast.hpp>

#include "AbstractRenderer.h"

#include "ShaderProgram.h"
#include "ShaderLocationsVault.h"
#include "ObjectInstance.h"
#include "nodes/LeafNode.h"

/*
    GLScenegraphRenderer is a visitor that implements SGNodeVisitor and will be
    used to traverse the scenegraph and render it */
class GLScenegraphRenderer: public AbstractRenderer {
    public:

    GLScenegraphRenderer(stack<glm::mat4>& mv, map<string,util::ObjectInstance *>& os, util::ShaderLocationsVault& shaderLocs);

    ~GLScenegraphRenderer();

    // to check for copy constructors
    GLScenegraphRenderer (GLScenegraphRenderer &t);

    void visitLeafNode(LeafNode *leafNode);

    private: 
    util::ShaderLocationsVault shaderLocations;
    map<string,util::ObjectInstance *> objects;

};

#endif