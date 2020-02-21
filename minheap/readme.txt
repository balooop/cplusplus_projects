This project implements a min heap using an array. The files I worked on were heap.cpp and heap.h. 
Functions implemented:
    1) root(): returns the root index of the heap
    2) leftChild(): returns the index of the left child of an input element
    3) rightChild(): returns the index of the right child of an input element
    4) parent(): returns the index of the parent of an input element
    5) empty(): returns a boolean indicating if the heap is empty
    6) hasAChild(): returns a boolean indicating if the input node has a child
    7) maxPriorityChild(): returns the index of the child element of an input node with the highest priorty (lowest value).
    8) heapifyDown(): ensures that the "heap" property is maintained using recursion to move a node down to its correct looation in the heap
    9) heapifyUp(): ensures that the "heap" property is maintained using recursion to move a node up to its correct looation in the heap
    10) heap(): constructor to build a heap
    11) pop(): removes the element with highest maxPriorityChild
    12) peek(): returns the value of the highest priority node without removing it
    13) updateElem(): updates the heap at an input index and maintains its heap property
This project was completed for CS225. All code not mentioned was provided by course staff.