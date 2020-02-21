This project implemented a BTree. The files I contributed to were btree.h and btree.cpp. More about BTrees can be found here: https://www.geeksforgeeks.org/introduction-of-b-tree-2/
Functions implemented:
    1) find(): this function searches a btree recursively for a key from an input subroot.
    2) split_child(): this is a helper function for insert. It splites a BTree node into two nodes, "throwing up" the new parent and making the two halves of the original tree childrens of the new parent.
    3) insert(): this function inserts a node into the BTree, adjusting it if needed.
This project was completed for CS225. All code not mentioned was provided by course staff