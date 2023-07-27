#ifndef _GROUPNODE_H_
#define _GROUPNODE_H_
#include <iostream>
#include <vector>

#include "../IScenegraph.h"
#include "ParentSGNode.h"

class GroupNode : public ParentSGNode {
    protected:
    ParentSGNode *copyNode() {
      return new GroupNode(name,scenegraph);
    }

    public:
    GroupNode(const std::string& name,IScenegraph *graph)
      :ParentSGNode(name,graph) {      
    }
	
    ~GroupNode() {
      
    }

    // add another child to this node
    void addChild(SGNode *child) {
      children.push_back(child);
      child->setParent(this);
    }

    SGNode *clone() {
      std::vector<SGNode *> newc;

      for (int i=0;i<children.size();i++) {
          newc.push_back(children[i]->clone());
      }

      GroupNode *newgroup = new GroupNode(name,scenegraph);

      for (int i=0;i<children.size();i++) {
          try
          {
            newgroup->addChild(newc[i]);
          }
          catch (std::runtime_error e)
          {

          }
      }
      return newgroup;
    }

    void setScenegraph(IScenegraph *graph) {
      AbstractSGNode::setScenegraph(graph);
      for (int i=0;i<children.size();i++)
      {
        children[i]->setScenegraph(graph);
      }
    }

    void accept(SGNodeVisitor* visitor) {
      std::cout << "Reached here" << std::endl;
    }

};
#endif