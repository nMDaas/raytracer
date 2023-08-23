#ifndef _TESTRENDERER_H_
#define _TESTRENDERER_H_

#include <stack>
#include <map>

#include <glm/gtx/string_cast.hpp>

#include "AbstractRenderer.h"

#include "ShaderProgram.h"
#include "ShaderLocationsVault.h"
#include "ObjectInstance.h"

#include "nodes/LeafNode.h"

class TestRenderer : public AbstractRenderer {
    
    public:
        TestRenderer(stack<glm::mat4>& mv, map<string,util::ObjectInstance *>& os, util::ShaderLocationsVault& shaderLocs);

        ~TestRenderer();

        // to check for copy constructors
        TestRenderer (TestRenderer &t);

        void visitLeafNode(LeafNode *leafNode);
        HitRecord& getHitRecord();

    private: 
        util::ShaderLocationsVault shaderLocations;
        map<string,util::ObjectInstance *> objects;
};

#endif