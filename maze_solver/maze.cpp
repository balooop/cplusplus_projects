/* Your code here! */
#include "maze.h"
#include <vector>
#include <queue>
#include <iostream>
#include <ctime>
#include <string>
#include <sys/time.h>

using namespace std;
using std::string;

//default constructor, does nothing
SquareMaze::SquareMaze() {  }

//creates a new SquareMaze of given height and witdh
void SquareMaze::makeMaze(int width, int height)
{ 
    //assigns width and height, compute size
    maze_height_ = height;
    maze_width_ = width;
    maze_size_ = maze_width_ * maze_height_;

    //add walls to every componenet of maze
    maze_set_.addelements(maze_size_);
    addAllWalls();

    int x_coord, y_coord;

    //cycle detection
    //make sure 2 nodes aren't in same set before removing wall
    //removing wall --> union two nodes connected by wall
    //if they are in the same set, we can't remove
    // srand(time(0));
    struct timeval tv;
    gettimeofday(&tv,NULL);
    srand(tv.tv_usec);
    // srand(time(NULL)%rand()%rand()+rand());
    while(maze_set_.size(0) < maze_size_)
    {
        //generates a random number based on time
        //gets a random number based on time
        x_coord = rand() % maze_width_;
        y_coord = rand() % maze_height_;


        //decides if we should delete right or down wall
        string right_or_down;
        if(rand() % 2 == 1)                 right_or_down = "right";
        else                                right_or_down = "down";

        //1D coordinate
        int coordinate_one_dim = y_coord * maze_width_ + x_coord;
        
        //delete right case:
        //check to see there won't be a cycle
        if  ( x_coord != maze_width_ - 1 &&
            right_or_down == "right" &&
            maze_set_.find(coordinate_one_dim) != maze_set_.find(coordinate_one_dim + 1)
            )
        {
            //makes sure we aren't at a perimeter
                //removes the wall
                setWall(x_coord, y_coord, 0, false);
                //unions the two uptrees
                maze_set_.setunion(coordinate_one_dim, coordinate_one_dim + 1);
        }

        //delete down case:
        //check to see there won't be a cycle
        else if  (y_coord != maze_height_ - 1&&
            right_or_down == "down" &&
            maze_set_.find(coordinate_one_dim) != maze_set_.find(coordinate_one_dim + maze_width_)
            )
        {
            //makes sure we aren't at a perimeter
                //removes the wall
                setWall(x_coord, y_coord, 1, false);
                //unions the two uptrees
                maze_set_.setunion(coordinate_one_dim, coordinate_one_dim + maze_width_);
        }
    }
    
}

//populates maze full of walls
void SquareMaze::addAllWalls()
{   
    //adds size pairs to wall vector
    for(int i = 0; i < maze_height_; i++)
    {
        vector<pair<bool,bool>> row;
        row.clear();
        for(int j = 0; j < maze_width_; j++)
        {
            row.push_back({true, true});
        }
        walls_.push_back(row);
    }
}

//sets a wall
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    if(dir == 0)                walls_[x][y].first = exists;
    else if(dir == 1)           walls_[x][y].second = exists;
}

//checks if we can travel from {x,y} in direction (dir)
bool SquareMaze::canTravel(int x, int y, int dir) const
{

    switch(dir){
    case 0: //right
      return ((walls_[x][y].first == false) ? true : false);
    case 1: //down
      return ((walls_[x][y].second == false) ? true : false);
    case 2: //left
      return (((x != 0) && (walls_[x-1][y].first == false)) ? true : false);
    case 3: //up
      return (((y != 0) && (walls_[x][y-1].second == false)) ? true : false);
  }
  return false;
}
    //makes sure we aren't at the end
    // switch(dir)
    // {
    //     //stepping right
    //     case 0:
    //         //make sure we aren't going past the end
    //         if((x + 1 < maze_width_) && (walls_[x+1][y].first != true))         return true;
    //         break;
    //     //stepping down
    //     case 1:
    //         //make sure we aren't going past the end and there's no wall
    //         if((y + 1 < maze_height_) && (walls_[x][y+1].second != true))        return true;
    //         break;
    //     //stepping left
    //     case 2: 
    //         //make sure we aren't going past the end and 
    //         if((x - 1 > -1) && (walls_[x-1][y].first != true))                  return true;
    //         break;
    //     //stepping up
    //     case 3: 
    //         if((y - 1 > -1) && (walls_[x][y-1].second != true))              return true;
    //         break;
    //     default:
    //         return false;
    //         break;
    // }
    // return false;

// }

vector<int> SquareMaze::solveMaze()
{
    /*
    *SETUP
    */
    //2D vectors of path from start to finish, previous nodes in path visited nodes, and distance
    //path vector, used later
    vector<int> directions_from_end;
    //previous nodes in path
    vector<vector<pair<int,int>>> previous;
    //visited points
    vector<vector<bool>> visited;
    //distance vector
    vector<vector<int>> distance;

    //marks all as unvisited
    //marks all distances as 0
    //marks all parents as zero zero pairs
    for(int r = 0; r < maze_width_; r++)
    {
        vector<bool> visited_rows;
        vector<int> distance_rows;
        vector<pair<int,int>> previous_rows;
        for(int c = 0; c < maze_height_; c++)
        {
            distance_rows.push_back(0);
            visited_rows.push_back(false);
            previous_rows.push_back({0,0});
        }
        visited.push_back(visited_rows);
        distance.push_back(distance_rows);
        previous.push_back(previous_rows);
    }
    //visits first space
    visited[0][0] = true;
    /*
    *END SETUP
    */

    /*
    *QUEUEING UP POINTS
    */
    //queue with points
    std::queue<pair<int,int>> q;
    //pushes start to queue
    q.push({0,0});
    //makes sure there are things in the queue
    while (q.size() > 0)
    {
        //gets the current point
        pair<int,int> current = q.front();
        q.pop();

        //sees if it can go in all directions
        vector<bool> can_go;
        for(unsigned i = 0; i < 4; i++)
        {
            can_go.push_back(canTravel(current.first, current.second, i));
        }
        //next, we add to queue if it can
        for(unsigned i = 0; i < can_go.size(); i++)
        {
            if(can_go[i] == true)
            {              
                pair<int,int> next_point = travelHelper(current, i);
                if(!visited[next_point.first][next_point.second])
                {
                    //marks as visited
                    visited[next_point.first][next_point.second] = true;
                    //updates distance from start
                    distance[next_point.first][next_point.second] = distance[current.first][current.second] + 1;
                    //marks path
                    previous[next_point.first][next_point.second] = {current.first, current.second};
                    //pushes point to queue
                    q.push(next_point);
                }
            }
        }
    }
    /*
    *END QUEUEING UP POINTS
    */

    /*
    *MAX DISTANCE
    */
    //end point
    pair<int,int> end_point;
    int max_height = maze_height_ - 1;

    //finds max distance for each point in bottom row
    //vector with only the bottom row
    vector<int> bottom_row_dist;
    for(int i = 0; i < maze_width_; i ++)
    {
        bottom_row_dist.push_back(distance[i][max_height]);
    }
    //gets x coordinate of maximum distance
    int max_dist = *(max_element(bottom_row_dist.begin(), bottom_row_dist.end()));
    int max_dist_x;
    for(int i = 0; i < maze_width_; i ++)
    {
        if(bottom_row_dist[i] == max_dist)  max_dist_x = i;
    }
    
    //coordinate pair of where the max distance is
    end_point = {max_dist_x, max_height};
    /*
    * END MAX DISTANCE
    */

    /*
    * CREATE PATH
    */
    while(end_point != pair<int,int>(0,0))
    {
        pair<int,int> parent = previous[end_point.first][end_point.second];
        //checks where prev was
        int dir = checkDirection(end_point, parent);
        //adds it to path from end
        if(dir != -1)
        {
            directions_from_end.push_back(dir);
        }
        //updates end point
        end_point = parent;
    }

    //gets start->end directions and returns
    std::reverse(directions_from_end.begin(), directions_from_end.end());
    return directions_from_end;
}  

//checks direction
int SquareMaze::checkDirection(pair<int,int> current, pair<int,int> parent)
{
    //previous x and y
    int prev_x = parent.first;
    int prev_y = parent.second;
    //current x and y
    int curr_x = current.first;
    int curr_y = current.second;

    //checks which direction parent is in from child
    if(prev_x + 1 == curr_x)                return 0;
    else if(prev_y + 1 == curr_y)           return 1;
    else if(prev_x - 1 == curr_x)           return 2;
    else if(prev_y - 1 == curr_y)           return 3;
    
    //catches errors
    return -1;
}

//returns point to be added to queue
pair<int,int> SquareMaze::travelHelper(pair<int,int> current, int dir)
{
    pair<int,int> toAdd;
    //creates point to add
    switch(dir)
    {
        case 0:
            toAdd = {current.first + 1, current.second};
            break;
        case 1:
            toAdd = {current.first, current.second + 1};
            break;
        case 2:
            toAdd = {current.first - 1, current.second};
            break;
        case 3:
            toAdd = {current.first, current.second - 1};
            break;
    }
    return toAdd;
}

//draws the maze without the solution
PNG * SquareMaze::drawMaze() const 
{ 
    //creates a maze of specified dimension 
    PNG * maze  = new PNG(maze_width_ * 10 + 1, maze_height_ * 10 + 1);
    //blacken top row (excl. x = 0 through 9)
    for(unsigned i = 10; i < maze->width(); i++)
    {
        //gets pixel
        HSLAPixel & cur = maze->getPixel(i, 0);
        //blackens 
        cur.l = 0;
    }
    //blacken left column
    for(unsigned i = 0; i < maze->height(); i++)
    {
        //gets pixel
        HSLAPixel & cur = maze->getPixel(0, i);
        //blackens 
        cur.l = 0;   
    }

    for(int x = 0; x < maze_width_; x++)
    {
        for(int y = 0; y < maze_height_; y++)
        {
            if(walls_[x][y].first){
                for(int k = 0; k < 11; k++)
                {
                    //gets pixel
                    HSLAPixel & cur = maze->getPixel( ( x + 1 ) * 10, y * 10 + k);
                    //blackens
                    cur.l = 0;
                }
            }
            if(walls_[x][y].second)
            {
                for(int k = 0; k < 11; k++)    
                {
                    //gets pixel
                    HSLAPixel & cur = maze->getPixel(x*10+k, (y+1)*10);
                    //blackens
                    cur.l = 0;
                } 
            }        
        }
    }
    return maze;
}
//draws the maze with the solution
PNG * SquareMaze::drawMazeWithSolution() 
{ 
    //solved PNG and color
    PNG * solved = drawMaze();
    HSLAPixel red(0,1,0.5,1);
    //solution
    vector<int> solution_steps = solveMaze();

    pair<unsigned, unsigned> cur = {5,5};
    //loops through
    for(unsigned i = 0; i < solution_steps.size(); i++)
    {
        switch(solution_steps[i])
        {
            //right
            case 0:
                //leaves red trail
                for(unsigned j = 0; j < 11; j++)
                {

                    HSLAPixel & p = solved->getPixel(cur.first + j, cur.second);
                    p.h = red.h;
                    p.s = red.s;
                    p.l = red.l;
                    p.a = red.a;
                }
                //updates cur
                cur = {cur.first + 10, cur.second};
                break;
            //down
            case 1:
                //leaves red trail
                for(unsigned j = 0; j < 11; j++)
                {

                    HSLAPixel & p = solved->getPixel(cur.first, cur.second + j);
                    p.h = red.h;
                    p.s = red.s;
                    p.l = red.l;
                    p.a = red.a;
                }
                //updates cur
                cur = {cur.first, cur.second + 10};
                break;
            //left
            case 2:
                //leaves red trail
                for(unsigned j = 0; j < 11; j++)
                {

                    HSLAPixel & p = solved->getPixel(cur.first - j, cur.second);
                    p.h = red.h;
                    p.s = red.s;
                    p.l = red.l;
                    p.a = red.a;
                }
                //updates cur
                cur = {cur.first - 10, cur.second};
                break;
            //up
            case 3:
                //leaves red trail
                for(unsigned j = 0; j < 11; j++)
                {

                    HSLAPixel & p = solved->getPixel(cur.first, cur.second - j);
                    p.h = red.h;
                    p.s = red.s;
                    p.l = red.l;
                    p.a = red.a;
                }
                //updates cur
                cur = {cur.first, cur.second - 10};
                break;
        }
    }
    // //fix exit
    cur.first -= 5;
    cur.second += 5;
    for(int k = 1; k <= 9; k++)
    {
        //gets pixel
        HSLAPixel & end = solved->getPixel(cur.first + k, cur.second);
        //whitens
        end.l = 1;
    }
    return solved;
}

PNG* SquareMaze::drawMazeCreative(){
    //creates a maze of specified dimension 
    PNG * maze  = new PNG(maze_width_ * 10 + 1, maze_height_ * 10 + 1);
    //blacken top row (excl. x = 0 through 9)
    for(unsigned i = 10; i < maze->width()/3 + 7; i++)
    {
        //gets pixel
        HSLAPixel & cur = maze->getPixel(i, 0);
        //blackens 
        cur.l = 0;
    }
    //blacken left column
    for(unsigned i = 0; i < maze->height(); i++)
    {
        //gets pixel
        HSLAPixel & cur = maze->getPixel(0, i);
        //blackens 
        cur.l = 0;   
    }

    //L bottom border
    for(unsigned x = maze->width()/3 + 7; x < maze->width(); x++)
    {
        unsigned y = maze->height() - (maze->height()/3) + 11;
        //gets pixel
        HSLAPixel & cur = maze->getPixel(x, y);
        //blackens 
        cur.l = 0;   
    }

    //L right border
    for(unsigned y = 0; y < maze->height() - (maze->height()/3) + 7; y ++)
    {
        unsigned x = maze->width()/3 + 7;
        //gets pixel
        HSLAPixel & cur = maze->getPixel(x, y);
        //blackens 
        cur.l = 0;   

    }

    //L shaped maze
    for(int x = 0; x < maze_width_; x++)
    {
        for(int y = 0; y < maze_height_; y++)
        {
            if(x <= maze_width_/3 && y <= (maze_height_ - (maze_height_/3))){
                if(walls_[x][y].first){
                    for(int k = 0; k < 11; k++)
                    {
                        //gets pixel
                        HSLAPixel & cur = maze->getPixel( ( x + 1 ) * 10, y * 10 + k);
                        //blackens
                        cur.l = 0;
                    }
                }
                if(walls_[x][y].second)
                {
                    for(int k = 0; k < 11; k++)    
                    {
                        //gets pixel
                        HSLAPixel & cur = maze->getPixel(x*10+k, (y+1)*10);
                        //blackens
                        cur.l = 0;
                    } 
                } 
            }
            else if (y > (maze_height_ - (maze_height_/3) ))
            {
               if(walls_[x][y].first){
                    for(int k = 0; k < 11; k++)
                    {
                        //gets pixel
                        HSLAPixel & cur = maze->getPixel( ( x + 1 ) * 10, y * 10 + k);
                        //blackens
                        cur.l = 0;
                    }
                }
                if(walls_[x][y].second)
                {
                    for(int k = 0; k < 11; k++)    
                    {
                        //gets pixel
                        HSLAPixel & cur = maze->getPixel(x*10+k, (y+1)*10);
                        //blackens
                        cur.l = 0;
                    } 
                } 
            }   
        }
    }
    return maze;

}