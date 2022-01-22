#include <iostream>
#include <vector>
#include "binaryTree.h"


int main(int argc, char** argv) {

    binaryTree* binTree = new binaryTree();
    std::vector<int> listOfNumbers = {4, 5, 10, 9, 8, 17, 49, 32, 23, 95, 59};
    for (int i = 0; i < listOfNumbers.size(); i++) {
        binTree->insert(listOfNumbers[i]);
    }

    binTree->inOrderTraversal();
    std::cout << std::endl;

    binTree->deleteFromTree(4);
    binTree->deleteFromTree(59);

    binTree->inOrderTraversal();
    std::cout << std::endl;

}