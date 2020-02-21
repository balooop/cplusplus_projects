This project implements BFS and DFS traversals of images, and also creates animated fills of images. The files I contributed to are imageTraversal/BFS.h, imageTraversal/BFS.cpp, imageTraversal/DFS.h, imageTraversal/DFS.cpp, imageTraversal/ImageTraversal.h, imageTraversal/ImageTraversal.cpp, FloodFilledImage.h, FloodFilledImage.cpp, colorPicker/MyColorPicker.h, colorPicker/MyColorPicker.h, and main.cpp.
The ImageTraversal, BFS, and DFS classes implement BFS and DFS traversals of images using iterators.
Functions Implemented:
    BFS/DFS
    1) constructor: creates a new BFS/DFS traversal for an images
    2) begin(): returns an iterator to the start of the BFS/DFS traversal
    3) end(): retursn an iterator to the end of the BFS/DFS traversal
    4) add(): adds a point to the BFS/DFS traversal queu
    5) pop(): removes and returns the current point in the BFS/DFS traversal
    6) peek(): returns the current point in the traversal
    7) empty(): returns a boolean as to whether the traversal queue is empty
    ImageTraversal implements a class that can iterate through images using either a DFS or BFS traversal
    1) calculateDelta(): finds the difference between two pixels using a euclidean formula
    2) Iterator(): initializes the ImageTraversal iterator. This function is overloaded
    3) operator++(): implements the increment operator for the imagetraversal. It appropriately adds another pixel to the BFS/DFS traversal queue
    4) operator*(): accesses the current point in the image traversal
    5) operator!-(): checks if two iterators are different
The FloodFilledImage class adds a type of flood-fill to an image and animates the filling of the iamge. The fill is chosen based on a type of colorPicker
Functions implemented:
    1) constructor: instantiates a FloodFilledImageObject
    2) addFloodFill(): adds a flood fill to the image using a an ImageTraversal and color colorPicker
    3) animate(): animates the flood filling of the image by adding frames at a set interval
The ColorPicker class selects colors to add to a FloodFilledImage
This project was completed for CS225. All components not mentioned above were provided by course staff.