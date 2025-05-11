#include <iostream>
#include "BinaryTree.h"

int main()
{
    BinaryTree tree;

    tree.addKey(10);
    tree.addKey(5);
    tree.addKey(15);
    tree.addKey(3);
    tree.addKey(7);
    tree.addKey(12);
    tree.addKey(18);
   
    tree.printHorizontal(tree.root(), 0, 5);
   
    std::cout <<"Height " << tree.Height(tree.root()) << std::endl;
    
    std::cout <<"Count " << tree.Count(tree.root()) << std::endl;
    
    std::cout <<"Maximum " << tree.findMinimum(tree.root()) << std::endl;
    std::cout << "Minimum " << tree.findMaximum(tree.root()) << std::endl;
 
    if (tree.removeNodeKey(12))
        std::cout << "Node removed\n";
    else
        std::cout << "Node not found\n";
    
    tree.printHorizontal(tree.root(), 0, 5);

    std::cout<< tree.Count(tree.root()) << std::endl;
    
    tree.clear();
    std::cout << "tree cleared. Empty? " << (tree.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}
