#ifndef _TESTRENDERER_H_
#define _TESTRENDERER_H_

#include <stack>
#include <map>

#include <glm/gtx/string_cast.hpp>

#include "AbstractRenderer.h"

#include "Material.h"
#include "HitRecord.h"

#include "nodes/LeafNode.h"
#include "../objects/Box.h"
#include "../objects/Sphere.h"

class TestRenderer : public AbstractRenderer {

    private: 
        glm::vec4 s;
        glm::vec4 v;

    public:
        TestRenderer(stack<glm::mat4>& mv, glm::vec4& in_s, glm::vec4& in_v);

        ~TestRenderer();

        // to check for copy constructors
        TestRenderer (TestRenderer &t);

        void visitLeafNode(LeafNode *leafNode);
        HitRecord& getHitRecord();

    private: 
        Box box;
        Sphere sphere;
        float minTime = INFINITY;
        util::Material* dummyMaterial;
        HitRecord hitRecordWithMinTime = {minTime,glm::vec4(0,0,0,0),glm::vec4(0,0,0,0),dummyMaterial};

        glm::vec4 getIntersection(float time, glm::vec4 _s, glm::vec4 _v);
        glm::vec4 getNormal(glm::vec4 intersectionPoint,string instanceOf);
};

#endif