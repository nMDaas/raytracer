#include "RaytracerRenderer.h"

RaytracerRenderer::RaytracerRenderer(){}
RaytracerRenderer::~RaytracerRenderer(){}

/*
    to check for copy constructors
*/
RaytracerRenderer::RaytracerRenderer (RaytracerRenderer &t) {
    std::cout << "RAYTRACERRENDERER COPY CONSTRUCTOR CALLED" << std::endl;
}

void RaytracerRenderer::visitGroupNode(GroupNode *groupNode);

void RaytracerRenderer::visitScaleTransform(ScaleTransform *scaleNode);

void RaytracerRenderer::visitRotateTransform(RotateTransform *rotateNode);

void RaytracerRenderer::visitTranslateTransform(TranslateTransform *translateNode);

void RaytracerRenderer::visitTransformNode(TransformNode *transformNode);

void RaytracerRenderer::visitLeafNode(LeafNode *leafNode);

void RaytracerRenderer::visitLightNode(LightNode *lightNode);

vector<util::Light> RaytracerRenderer::getLights();

void RaytracerRenderer::clearLights();