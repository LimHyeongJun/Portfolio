#ifndef __TREE_H__
#define __TREE_H__

#include "TreeNode.hpp"

class Tree {
  public:
    Tree();
    Tree(int data);

    void insert(int data);
    void display();
    bool search(int data);
    bool remove(int data);

  private:
    void display(TreeNode *curNode);
    TreeNode *rootnode;
    int getMax(TreeNode *rootNode);
};

#endif
