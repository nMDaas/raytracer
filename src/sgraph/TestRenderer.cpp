#include "TestRenderer.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"

TestRenderer::TestRenderer(stack<glm::mat4>& mv, glm::vec4& in_s, glm::vec4& in_v) 
: AbstractRenderer(mv), s(in_s), v(in_v) {}

TestRenderer::~TestRenderer() {

}

// to check for copy constructors
TestRenderer::TestRenderer (TestRenderer &t) : AbstractRenderer(t.modelview), s(t.s), v(t.v) {
    std::cout << "TestRenderer COPY CONSTRUCTOR CALLED" << std::endl;
}

void TestRenderer::visitLeafNode(LeafNode *leafNode) {
    spdlog::info("visitLeafNode(): " +leafNode->getName());
}