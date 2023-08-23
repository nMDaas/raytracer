#ifndef _TESTRENDERER_H_
#define _TESTRENDERER_H_

#include <stack>
#include <map>

#include <glm/gtx/string_cast.hpp>

#include "AbstractRenderer.h"

#include "nodes/LeafNode.h"

class TestRenderer {

    public:
        TestRenderer();

        ~TestRenderer();

        // to check for copy constructors
        TestRenderer (TestRenderer &t);
};

#endif