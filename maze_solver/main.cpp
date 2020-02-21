#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze s;
    s.makeMaze(100, 100);
    PNG * creative = s.drawMazeCreative();
    creative->writeToFile("creative.png");
    return 0;
}
