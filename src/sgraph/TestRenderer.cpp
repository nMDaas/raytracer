#include "TestRenderer.h"

TestRenderer::TestRenderer() {
    
}

TestRenderer::~TestRenderer() {

}

// to check for copy constructors
TestRenderer::TestRenderer (TestRenderer &t) : AbstractRenderer(t.modelview), s(t.s), v(t.v) {
    std::cout << "TestRenderer COPY CONSTRUCTOR CALLED" << std::endl;
}