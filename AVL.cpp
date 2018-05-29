//
// Created by Tucker Zischka on 5/28/2018.
//
#include "AVL.h"
#include <stdlib.h>
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <string>

int AVLTree :: height(BST &BSTTree){
 int currentHeight = -1;
 height(currentHeight, BSTTree.root());

}

int AVLTree :: height(int &currentHeight, std::shared_ptr<BSTNode> currentNode){
    if(currentNode->IsLeaf()) {
        return currentHeight + 1;
    }

    int rightHeight = 0;
    int leftHeight = 0;
    //Left Height
    if(currentNode->HasLeftChild()) {
        /***********Left Node **************/
        leftHeight = height(currentHeight, currentNode->getLeft());
    }
    //Right Height
    if(currentNode->HasRightChild()) {
        /************Right Node*************/
        rightHeight = height(currentHeight, currentNode->getRight());
    }

    currentHeight = (rightHeight<leftHeight)?leftHeight:rightHeight;
    currentNode->setHeight(currentHeight);

    return currentHeight + 1;
}
void AVLTree ::balanceFactor(BST &BSTTree) {
    balanceFactor(BSTTree.root());
}
/*========================BF = RightHeight - LeftHeight=========================*/
void AVLTree ::balanceFactor(std::shared_ptr<BSTNode> currentNode) {
    if(currentNode->IsLeaf()){
        currentNode->setBalance(0);
    }
    /*************Left Branch**************/
    if(currentNode->HasLeftChild()){
        balanceFactor(currentNode->getLeft());
    }


    /*************Right Branch*************/
    if(currentNode->HasRightChild()){
        balanceFactor(currentNode->getRight());
    }

    if (currentNode->HasLeftChild() && currentNode->HasRightChild()){
        currentNode->setBalance(currentNode->getRight()->getHeight() - currentNode->getLeft()->getHeight());
    }
    else if (currentNode->HasRightChild()){
        currentNode->setBalance(currentNode->getRight()->getHeight());
    }
    else if(currentNode->HasLeftChild()){
        currentNode->setBalance(currentNode->getLeft()->getHeight());
    }





    /*=====================Balancing Code =====================*/
    if (currentNode->getBalance() > 1) { // Greater than 1 (Right heavy)
        if( currentNode->getRight()->getBalance()) { //right heavy one (R-R)
            AVLTree::RRBalance(currentNode);
        }
        if (currentNode->getLeft()->getBalance()) { //left heavy one (R-L)
            AVLTree::RLBalance(currentNode);
        }

    }
    if (currentNode->getBalance() < -1) { //Less than 1 (Left heavy)
        if( currentNode->getRight()->getBalance()) { //right heavy one (L-R)
            AVLTree::LRBalance(currentNode);
        }
        if (currentNode->getLeft()->getBalance()) { //left heavy one (L-L)
            AVLTree::LLBalance(currentNode);
        }
    } else {
        //Nothing because it only needs to work when bf is over |1|
    }




}
void AVLTree ::RRBalance(std::shared_ptr<BSTNode> currentNode) { //Left rotation
    AVLTree::leftRotation(currentNode->getRight());
}
void AVLTree ::RLBalance(std::shared_ptr<BSTNode> currentNode) { //Right roation than left rotation
    AVLTree::rightRotation(currentNode->getRight()->getLeft());
    AVLTree::leftRotation(currentNode->getRight());
}
void AVLTree ::LLBalance(std::shared_ptr<BSTNode> currentNode) { //right rotation
    AVLTree::rightRotation(currentNode->getLeft());
}
void AVLTree ::LRBalance(std::shared_ptr<BSTNode> currentNode) { //Left rotation than Right rotation
    AVLTree::leftRotation(currentNode->getLeft()->getRight());
    AVLTree::rightRotation(currentNode->getLeft());
}


/* Follow this to get a sense of the rotations that we need
 * http://images-mediawiki-sites.thefullwiki.org/05/2/2/0/54834251380407153.gif
 */

void AVLTree::rightRotation(std::shared_ptr<BSTNode> currentNode){
    std::shared_ptr<BSTNode> pivot = currentNode;
    std::shared_ptr<BSTNode> root = currentNode->getParent().lock();
    //check if any child nodes exist
    if(pivot->HasRightChild()){
        //roots left child equal to pivots right child
        root->ReplaceChild(pivot, pivot->getRight());
    }
    //set pivot's right child to root
    pivot->ReplaceChild(pivot->getRight(), root);
    //set pivot's new parent
    pivot->setParent(root->getParent());
    //Set pivots new parent's child to pivot
    std::shared_ptr<BSTNode> parent = pivot->getParent().lock();
    parent->ReplaceChild(root, pivot);
    //Set roots parent to pivot
    root->setParent(pivot);
}
void AVLTree::leftRotation(std::shared_ptr<BSTNode> currentNode) {
    std::shared_ptr<BSTNode> pivot = currentNode;
    std::shared_ptr<BSTNode> root = currentNode->getParent().lock();
    //check if any child nodes exist
    if(pivot->HasLeftChild()){
        //roots right child equal to pivots left child
        root->ReplaceChild(pivot, pivot->getLeft());
    }
    //set pivot's left child to root
    pivot->ReplaceChild(pivot->getLeft(), root);
    //set pivot's new parent
    pivot->setParent(root->getParent());
    //Set pivots new parent's child to pivot
    std::shared_ptr<BSTNode> parent = pivot->getParent().lock();
    parent->ReplaceChild(root, pivot);
    //Set roots parent to pivot
    root->setParent(pivot);
}







void AVLTree :: inputFunc(std::string arg1){
    std::ifstream file;
    file.open(arg1); //make sure to use ./../filename.json as the input. The .'s and /'s are nessacary
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
    }

    auto itr = jsonObject.begin();
    BST AVLTree;
    int numOperations = 0;
    while(jsonObject[itr.key()] != "metadata"){
        std::string command = jsonObject[itr.key()]["operation"];
        if(command == "Insert") {
            AVLTree.Insert(jsonObject[itr.key()]["key"]);
            AVLTree::height(AVLTree);
            AVLTree::balanceFactor(AVLTree);
            AVLTree::height(AVLTree);
        }  else if (command == "Delete") {
            AVLTree.Delete(jsonObject[itr.key()]["key"]);
            AVLTree::height(AVLTree);
            AVLTree::balanceFactor(AVLTree);
            AVLTree::height(AVLTree);
        } else if (command == "DeleteMin"){
            AVLTree.DeleteMin();
            AVLTree::height(AVLTree);
            AVLTree::balanceFactor(AVLTree);
            AVLTree::height(AVLTree);
        }
        ++numOperations;
        ++itr;
    }
}

void AVLTree :: output() {

}

