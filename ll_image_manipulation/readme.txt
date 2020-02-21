This project uses linked lists, template classes, and iterators to perform various functions on lists. The files I contributed to were List-ListIterator.hpp, List.h, and List.hpp.
The ListIterator class iterates through a linked list.
Functions implemented:
    1) operator++: implements the functionality for the preincrement/postincrement iterator function for linked lists
    2) operator--: implements the functionality for the predecrement/postdecrement iterator function for linked lists
    3) operator!=: checks if two iterators are not the same
    4) operator==: checks if two iterators are the same
    5) operator*: returns the item at the position of the current iterator
    6) operator->: performs the (*iter). functionality through using the -> operator
    8) ListIterator begin(): returns an iterator at the start of the list
    9) ListIterator end(): returns an iterator one beyond the end of the list
The list class implements various functions for a linked list.
Functions implemented:
    1) constructor: constructs the list object
    2) _destroy(): helper function to destroy all dynamically allocated memory from the list
    3) insertFront(): inserts a new node at the front of the list
    4) insertBack(): inserts a new node at the back of the list
    5) split(): helper function that splits a node a certain number of nodes after a designated start node
    6) waterfall(): uses the waterfall algorithm to change the list. It moves every other object in a list to the end of the list
    7) reverse(): reverses the list by calling the helper function
    8) reverse(): helper function for reverse, reverses all nodes between a start and end point
    9) reverseNth(): reverses blocks of input size n within the linked list
    10) mergeWith(): merges two sorted lists
    11) merge(): helper function that merges two sorted lists and keeps the whole list sorted
    12) mergesort(): implements the mergesort algorithm on two linked lists
The program uses these linked lists to perform image manipulations, which can be seen in the /tests folder. 
This project was completed for CS225. All materials not mentioned were provided by course staff.
    