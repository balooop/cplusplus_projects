This program implements a way to encode and decode Huffman Code messages using a tree. See more about the Huffman Encoding here: https://www.techiedelight.com/huffman-coding/ 
The functions I contributed were buildTree(), decode(), removeSmallest(), writeTree(), and readTree().
    1) buildTree(): builds a HuffmanTree based on frequencies using two queues: one containing inner nodes, and one containing leaf nodes. 
    2) removeSmallest(): a helper function for buildTree(), removes the between node from two queues.
    3) decode(): decodes a binary file that contains a Huffman encoded message by traversing the tree and prints it to a stringstream. 
    4) writeTree(): writes a Huffman encoding tree into a binary file
    5) readTree(): reads bits of a file and creates a binary tree out of it using recusrion.
This project was completed for CS225. All materials not mentioned were provided by course staff.