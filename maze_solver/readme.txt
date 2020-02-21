This project generates and solves a maze of variable size using disjoint sets. THe files I contributed to were dsets.h, dsets.cpp, maze.h, maze.cpp, and main.cpp.
More on the Disjoint Sets infrastructure can be found here: https://www.geeksforgeeks.org/disjoint-set-data-structures/.
For this project, the Disjoint Sets structure was implemented using an up-tree representation with an array-based implementation.
Functions implemented: 
    1) addelements(): adds an element to the disjoint set
    2) find(): finds an element in the data structure. Implements path compression
    3) setunion(): performs a union-by-size for two disjoint sets, merging smaller size uptree into the larger one
    4) size(): returns the size of the disjoint set containing a certain element.
The SquareMaze class was implemented in maze.h and maze.cpp. It contains functions to create a randomly generated square maze, and then solves the maze.
Functions implemented:
    1) makeMaze(): makes a maze with a given size. Randomly generates walls for the maze.
    2) addAllWalls(): adds walls to the 2D vector of pairs represnetations of walls.
    3) setWall(): sets a wall at a given location in the maze in a given direction
    4) canTravel(): function that checks if we can travel from a certain {x,y} coordinate on the maze in a given direction
    5) solveMaze(): solves the maze and returns the solution as a vector of moves to the finish point furthest from the start point
    6) checkDirection(): checks the direction a node is from its parent node
    7) travelHelper(): helper function created to figure out which point to add to the set of moves in solution
    8) drawMaze(): draws the unsolved maze to a PNG
    9) drawMazeWithSolution(): draws a solved maze with a line indicating the solution to a PNG
    10) drawMazeCreative(): draws an L-shaped unsolved maze to a PNG
This project was completed for CS225. All materials not mentioned above were provided by course staff.