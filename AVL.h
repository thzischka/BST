//
// Created by Tucker Zischka on 5/28/2018.
//
#include "BST.h"

#ifndef PROGRAM3_AVL_H
#define PROGRAM3_AVL_H

class AVLTree {
public:
    int height(BST &BSTTree);
    int height(int &currentHeight, std::shared_ptr<BSTNode> currentNode);
    void balance();
    void balanceFactor(BST &BSTTree);
    void balanceFactor(std::shared_ptr<BSTNode> CurrentNode);

    void inputFunc(std::string arg1);
    void output();

private:
    void RRBalance(std::shared_ptr<BSTNode> grandpaNode);
    void RLBalance(std::shared_ptr<BSTNode> grandpaNode);
    void LLBalance(std::shared_ptr<BSTNode> grandpaNode);
    void LRBalance(std::shared_ptr<BSTNode> grandpaNode);
    void rightRotation(std::shared_ptr<BSTNode> currentNode);
    void leftRotation(std::shared_ptr<BSTNode> currentNode);

};


#endif //PROGRAM3_AVL_H
