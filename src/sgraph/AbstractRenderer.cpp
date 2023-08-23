#include "AbstractRenderer.h"
#include <iostream>

AbstractRenderer::AbstractRenderer(){}

AbstractRenderer::~AbstractRenderer(){}

// to check for copy constructors
AbstractRenderer::AbstractRenderer (AbstractRenderer &t) {
    std::cout << "AbstractRenderer COPY CONSTRUCTOR CALLED" << std::endl;
}