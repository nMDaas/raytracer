#ifndef _LEAFNODE_H_
#define _LEAFNODE_H_

#include "Material.h"
#include "TextureImage.h"

#include "ChildSGNode.h"
#include "../IScenegraph.h"
#include "SGNode.h"

/* LeafNode extends ChildSGNode */
class LeafNode: public ChildSGNode {
    protected: 
    util::Material material;
    string objInstanceName;

    public: 
    LeafNode(const std::string& instanceOf,util::Material& material,const std::string& name,IScenegraph *graph);

    LeafNode(const std::string& instanceOf,const std::string& name,IScenegraph *graph);

    // sets material of all vertices in this object
    void setMaterial(const util::Material& mat);

    SGNode *clone();

    string getInstanceOf();

    util::Material* getMaterial();

    void accept(SGNodeVisitor* visitor);

    void setTexture(TextureImage* textImage);
    
    TextureImage* getTexture();

    private : 
    TextureImage* textureImage;
};

#endif