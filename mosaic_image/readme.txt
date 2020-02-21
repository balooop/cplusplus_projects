This project utilizes KD-Trees to create a mosaic image. A mosaic image creates a larger, "base" image by using hundreds of smaller images to create a replica of that image. 
The mosaic image can be found at mymosaic.png.
KD-Trees were used for their nearest-neighbour search functionality. Images were sorted into the KD-Tree, when constructing the mosaic image, the KD-Tree was searched to find an image closest to the color of that section of the base image.
The files I contributed to were maptiles.h, maptiles.cpp, kdtree.h, kdtree.hpp, PARTNERS.txt, mymosaic.png
The KD-Tree class implements a KD-Tree
Functions implemented:
    1) smallerDimVal(): finds the point with a smaller value in the specified dimension
    2) shouldReplace(): checks if a point is closer to a target point than the current closest point
    3) calculateDistance(): computes the euclidean distance between two points
    4) KDTree(): constructor for the KD-Tree, calls upon the _construct() function to construct it
    5) _construct(): recursive helper function to construct the KD-Tree, see the code comments for more specifications
    6) _quickselect(): utilizes the quick select algorithm to find the median element in a set of indexes
    7) _partition(): helper function for quickselect that partitions elements
    8) copy constructor: creates a deep copy of another KD-Tree
    9) operator=: overloaded equals operator 
    10) destructor: destroys KD-Tree and frees all associated memory
    11) _copy and _destroy: helper functions for constructors, destructor, and = operator
    12) findNearestNeighbour(): calls travelDown() to find perform a nearest neighbour search
    13) travelDown(): recursively helper function for the nearest neighbour search, calls upon other functions written in the class
mapTiles is a clsas/function that takes in a source image and a vector of tile images and maps the tile images to rectangular regions of the source image. This creates the mosaic image for this project
This project was completed for CS225. All materials not mentioned were provided by course staff.