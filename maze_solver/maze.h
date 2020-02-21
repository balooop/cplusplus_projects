/* Your code here! */
#pragma once

#include <stdint.h>
#include <vector>
#include <utility>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"

using namespace cs225;
using namespace std;

class SquareMaze
{
    private:
        int maze_width_;
        int maze_height_;
        int maze_size_;
        DisjointSets maze_set_;
        //2D array of pairs for walls
        //pair.first = right
        //pair.second = down
        vector<vector<pair<bool, bool>>> walls_;

        //helper functions
        //helper for createmazes
        void addAllWalls();
        //helper for solve maze travelling
        pair<int,int> travelHelper(pair<int,int> current, int dir);
        //helper for solve maze solution directios
        int checkDirection(pair<int,int> current, pair<int,int> parent);
     
    public:
        //default constructor
        SquareMaze();
        //creates a maze with width and height parameter
        void makeMaze(int width, int height);
        //checks if we can travel in the direction (dir) from {x,y}
        bool canTravel(int x, int y, int dir) const;
        //sets whether or not the specified wall exists from {x,y} in the specified direction (dir)
        void setWall(int x, int y, int dir, bool exists);
        //solves the square maze
        vector<int> solveMaze();
        //draws the maze without the solution
        PNG * drawMaze() const;
        //draws the maze with the solution
        PNG * drawMazeWithSolution();
        //part 3
        PNG* drawMazeCreative();
};