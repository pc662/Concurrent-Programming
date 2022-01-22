#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <mutex>
#include <condition_variable>
#include <iostream>


class binaryTree {
    //private attributes
    private:
        //A struct for each node in the binary tree
        struct node {
            int key;
            node* leftChild;
            node* rightChild;
        };
        //Current pointer
        node* currentPointer;
        //Root pointer
        node* root;
        //Locks for the binary tree
        mutable std::mutex mtx;
        
    //public methods
    public:
        //Creates an empty tree
        binaryTree();
        //Insert value into the tree
        void insert(int value);
        //Helper function to insert a value into the tree
        binaryTree::node* insertValue(int value, node* current);
        //Delete from the tree
        void deleteFromTree(int value);
        //Delete a value from the tree
        binaryTree::node* deleteValue(int value, node* root);
        //Delete a node from the tree
        binaryTree::node* deleteNode(node* node);
        //Find the min starting at a node
        int findMinimum(node* startingNode);
        //Search for a value and return the node if it exists
        std::string searchTree(int value);
        //Helper function for the searchTree
        bool search(int value, node* current);
        //Print the BST in order
        void inOrderTraversal();
        //Helper function for the inOrder Traversal
        void inOrder(node* root);



};


binaryTree::binaryTree() {
    node* root = NULL;
    node* current = NULL;
}


void binaryTree::insert(int value) {
    std::lock_guard<std::mutex> lk(mtx);
    currentPointer = insertValue(value, root);
}

binaryTree::node* binaryTree::insertValue(int value, node* current) {

    //Once the current node is null, create the new node with the new value
    if (current == NULL) {
        node* newNode = new node();
        newNode->key = value;
        newNode->rightChild = NULL;
        newNode->leftChild = NULL;
        //If there is no root, this is root
        if (root == NULL) {
            root = newNode;
        }
        //Return the value for the new inserted node to recursively update pointers
        return newNode;
    }

    //If the current value is the same, then just return the current pointer and don't add anything
    else if (current->key == value) {
        return current;
    }

    //Update right side
    else if (value > current->key) {
        current->rightChild = insertValue(value, current->rightChild);
    }

    //Update left side
    else if (value < current->key) {
        current->leftChild = insertValue(value, current->leftChild);
    }

    return current;
}

void binaryTree::deleteFromTree(int value) {
    std::lock_guard<std::mutex> lk(mtx);
    currentPointer = deleteValue(value, root);
}

binaryTree::node* binaryTree::deleteValue(int value, node* current) {
    //If it doesn't exist, then nothing
    if (current == NULL) {
        return NULL;
    }

    //If we found the value
    else if (current->key == value) {
        node* replacementNode = deleteNode(current);
        if (current == root) {
            root = replacementNode;
        }
        return replacementNode;
    }

    //If the value is greater than current, then search right
    else if (value > current->key) {
        current->rightChild = deleteValue(value, current->rightChild);
    }

    //If the value is less than current, then search left
    else if (value < current->key) {
        current->leftChild = deleteValue(value, current->leftChild);
    }

    return current;
}

binaryTree::node* binaryTree::deleteNode(node* nodeToBeDeleted) {

    //If there is no left child, then replace with the right child
    if (nodeToBeDeleted->leftChild == NULL) {
        return nodeToBeDeleted->rightChild;
    }

    //If there is no right child, then replace with the left child
    else if (nodeToBeDeleted->rightChild == NULL) {
        return nodeToBeDeleted->leftChild;
    }

    //Swapping with the minimum value on the right side
    int minValue = findMinimum(nodeToBeDeleted->rightChild);
    //Swap the min
    nodeToBeDeleted->key = minValue;
    //Delete from the right
    nodeToBeDeleted->rightChild = deleteValue(minValue, nodeToBeDeleted->rightChild);
    //Return the new pointer
    return nodeToBeDeleted;
}

int binaryTree::findMinimum(node* startingNode) {
    if (startingNode->leftChild == NULL) {
        return startingNode->key;
    } else {
        return findMinimum(startingNode->leftChild);
    }
}

std::string binaryTree::searchTree(int value) {
    bool found = search(value, root);
    if (found == true) {
        return "found";
    } else {
        return "not found";
    }
}

bool binaryTree::search(int value, node* current) {
    //If the value is not found in the tree
    if (current == NULL) {
        return false;
    }

    //If the value is found in the tree
    else if (current->key == value) {
        return true;
    }

    //Search right side
    else if (current->key < value) {
        return search(value, current->rightChild);
    }

    //Search left side
    return search(value, current->leftChild);
}

void binaryTree::inOrderTraversal() {
    inOrder(root);
}

void binaryTree::inOrder(node* node) {
    if (node == NULL) {
        return;
    }
    
    inOrder(node->leftChild);
    std::cout << node->key << " ";
    inOrder(node->rightChild);
}


#endif

