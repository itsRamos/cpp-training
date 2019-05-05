//**********************************************************************************
// Integer Balanced BST
// This program builds an integer binary search tree of 5 nodes.
// First to use the enclosed draw() helper to show the BST upon each node insertion.
// Then display the BST content with inorder, preorder, and postorder traversal.
/// Author: Erick Ramos
/// Date: November 20, 2017
///***********************************************************************************
#ifndef INTBINARYTREE_H
#define INTBINARYTREE_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class IntBinaryTree
{
private:
  struct TreeNode {
     int value;     
     TreeNode *left;
     TreeNode *right;
  };

  TreeNode *root;
  // Private helpers - use recursion
  void insert(TreeNode *&, TreeNode *&);
  void remove(TreeNode *&, int);
  void makeDeletion(TreeNode *&);
  void destroySubTree(TreeNode *&);
  void displayInOrder(TreeNode *) const;
  void displayPreOrder(TreeNode *) const;
  void displayPostOrder(TreeNode *) const;
   
public:
   IntBinaryTree() { root = nullptr; }
   ~IntBinaryTree() {destroySubTree(root); }
   void insert(int);
   void clear(){destroySubTree(root);root = nullptr; }
   void remove(int value) { remove(root, value); }
   void displayInOrder() const { displayInOrder(root); }
   void displayPreOrder() const { displayPreOrder(root); }
   void displayPostOrder() const { displayPostOrder(root); }
   void draw(TreeNode* tree, std::string lpad, std::string rpad) const {
      std::string pad = lpad.substr(0, lpad.size() - 1);
      if (tree == nullptr)	return;
      draw(tree->right, rpad + "    |", rpad + "     ");
      std::cout << pad << "+--" << std::setw(3) << tree->value << std::endl;
      draw(tree->left, lpad + "     ", lpad + "    |");
   }

   void draw() const {
      std::cout << std::endl;
      this->draw(root, " ", " ");
      // std::cout << std::endl;
   }
   //void sorted2BST();
};

////////////////////// private Helpers
void IntBinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode) {
    if(nodePtr == nullptr){
        nodePtr = newNode;
    }
    else if(newNode -> value < nodePtr -> value){
        insert(nodePtr -> left, newNode);
    }
    else{
        insert(nodePtr -> right, newNode);
    }
}
 void IntBinaryTree::remove(TreeNode *&node, int value) {
     if (value < node->value){
         remove(node->left, value);
     }
     else if(value > node->value)
        remove(node->right, value);
    else makeDeletion(node);
 }
void IntBinaryTree::makeDeletion(TreeNode *&node) {
    TreeNode *temp;
    // 0.5 one child (or no child) right/left subtree
    if(!node->right) { // no child case not covered
        temp = node;
        node = node->left;
        delete temp;
    }
    else if(!node->left) {
        temp = node;
        node = node->right;
        delete temp;
    }
    else { //1. find right subtree leftmost node
        temp = node->right;
        TreeNode *leftMostNode = temp;
        while(leftMostNode->left) {
            leftMostNode = leftMostNode->left;
            if(!leftMostNode->left) break;
            temp = leftMostNode;
        }
        
        // 2. prmote leftMost value to node (target)
        node->value = leftMostNode->value;
        
        // 2.1 leftMost is the node's immediate right child
        if(leftMostNode == node->right)
            if(!leftMostNode->right) node->right = nullptr;
            
        // 3. leftMost has no right child
        if(!leftMostNode->right) temp->left = nullptr;
        else // 3.1 leftMost has a right child
             // raise the leftMost->right as grandpa's left child
            temp->left = leftMostNode->right;
        
        // 4. recycle
        delete leftMostNode;
    }
}
void IntBinaryTree::destroySubTree(TreeNode *&node) {
    if(node){
        if(node -> left)
            destroySubTree(node -> left);
        if(node -> right)
            destroySubTree(node -> right);
        delete node;
    }
}
void IntBinaryTree::displayInOrder(TreeNode *node) const {
    if(node){
        displayInOrder(node -> left);
        cout << node -> value << " ";
        displayInOrder(node -> right);
    }
}


void IntBinaryTree::displayPreOrder(TreeNode *node) const {
    if(node){
        cout << node -> value << " ";
        displayPreOrder(node -> left);
        displayPreOrder(node -> right);
    }
}

void IntBinaryTree::displayPostOrder(TreeNode *node) const {
    if(node){
        displayPostOrder(node -> left);
        displayPostOrder(node -> right);
        cout << node -> value << " ";
    }
}

////////////////////// Public Method
void IntBinaryTree::insert(int value) {
    TreeNode *newNode = nullptr;
    newNode = new TreeNode;
    newNode -> value = value;
    newNode -> left = newNode -> right = nullptr;
    insert(root, newNode);
}

#endif
