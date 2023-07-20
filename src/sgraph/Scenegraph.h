#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_
#include <string>
#include <map>

#include "IScenegraph.h"


// an implementation of IScenegraph
class Scenegraph: public IScenegraph {
    protected:
        SGNode *root;
        std::map<std::string,SGNode *> nodes; // to keep track of all nodes in this scenegraph

    public:
    Scenegraph() {
      root = NULL;
    }

    ~Scenegraph() {
      if (root!=NULL) {
          delete root;
          root = NULL;
      }
    }

    // add a node to the scenegraph to keep track of all nodes
    void addNode(const std::string& name, SGNode *node) {
      nodes[name]=node;
    }
};

#endif