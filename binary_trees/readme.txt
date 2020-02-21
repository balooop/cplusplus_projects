This project involved implementing a binary tree and various associated functions and subclasses. The files I contributed to in this repository are: TreeTraversals/InorderTraversal.h, binarytree.h, and binarytree.cpp.
The InorderTraversal class utilized a stack and iterators to maintain a preorder traversal of the binary tree. Within the InorderTraversal class, I implemented the following:
    1) isOrdered(): checks if the inorder traversal class returns a nondecreasing output of numbers
        - This function was implemented twice, once recursively and once iteratively
    2) Constructor
    3) add: given a node in the tree, add the next appropriate nodes to a stack s.t. when popped, they produce an inorder traversal
Within the BinaryTree class, I implemented the header file and the associated cpp file, including:
    1) height(): compute the height of the binary tree
    2) printLeftToRight(): prints the nodes of the binary tree inorder
    3) mirror(): flips the binary tree over its vertical axis (aka root)
This project was done for CS225, and all code not mentioned was provided by course staff.