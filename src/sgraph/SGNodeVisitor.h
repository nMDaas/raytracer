#ifndef _SGNODEVISITOR_H_
#define _SGNODEVISITOR_H_

class GroupNode;
class ScaleTransform;
class TranslateTransform;
class RotateTransform;
class TransformNode;
class LeafNode;
class LightNode;

// this is an interface for any visitor that will be accepted by the scenegraph
class SGNodeVisitor {
        public:
        virtual void visitGroupNode(GroupNode *node)=0;
        virtual void visitScaleTransform(ScaleTransform *node)=0;
        virtual void visitTranslateTransform(TranslateTransform *node)=0;
        virtual void visitRotateTransform(RotateTransform *node)=0;
        virtual void visitTransformNode(TransformNode *node)=0;
        virtual void visitLeafNode(LeafNode *node)=0;
        virtual void visitLightNode(LightNode *node)=0;
};

#endif