#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_
#include <string>

#include "IScenegraph.h"


// an implementation of IScenegraph
class Scenegraph: public IScenegraph {
    protected:
        SGNode *root;

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
};

#endif