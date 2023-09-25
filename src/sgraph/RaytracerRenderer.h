#ifndef _RAYTRACERRENDERER_H_
#define _RAYTRACERRENDERER_H_
#include <stack>
#include <map>

#include <glm/gtx/string_cast.hpp>

#include "AbstractRenderer.h"

#include "Material.h"
#include "HitRecord.h"

#include "nodes/LeafNode.h"
#include "../objects/Box.h"
#include "../objects/Sphere.h"
#include "../objects/Cylinder.h"
#include "../objects/Cone.h"

/* RaytraceRenderer is a visitor that extends AbstractRenderer and 
will be used to traverse the scenegraph and return a HitRecord */
class RaytracerRenderer: public AbstractRenderer {
    public:

        RaytracerRenderer(stack<glm::mat4>& mv, glm::vec4& in_s, glm::vec4& in_v);
        ~RaytracerRenderer();

        // to check for copy constructors
        RaytracerRenderer (RaytracerRenderer &t);

        void visitLeafNode(LeafNode *leafNode);
        HitRecord& getHitRecord();


    private: 
    glm::vec4 s;
    glm::vec4 v;
    Box box;
    Sphere sphere;
    Cylinder cylinder;
    Cone cone;
    float minTime = INFINITY;
    util::Material* dummyMaterial;
    TextureImage* dummyTextureImage;
    HitRecord hitRecordWithMinTime = {minTime,glm::vec4(0,0,0,0),glm::vec4(0,0,0,0),dummyMaterial,dummyTextureImage,glm::vec2(0,0), ""};

    glm::vec4 getIntersection(float time, glm::vec4 _s, glm::vec4 _v);
    glm::vec4 getNormal(glm::vec4 intersectionPoint, string instanceOf);
    glm::vec2 getTextureCoordinates(glm::vec4 intersectionPoint, string instanceOf);

};

#endif