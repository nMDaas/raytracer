#include "TestRenderer.h"

TestRenderer::TestRenderer() {
    
}

TestRenderer::~TestRenderer() {

}

// to check for copy constructors
TestRenderer::TestRenderer (TestRenderer &t) {
    std::cout << "TestRenderer COPY CONSTRUCTOR CALLED" << std::endl;
}