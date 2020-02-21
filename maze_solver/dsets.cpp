/* Your code here! */
#include "dsets.h"

using namespace std;


//adds an unconnected element to the set
void DisjointSets::addelements(int num)
{
    //creates num number of unconnected nodes (unconnected nodes are root nodes, so they are -1)
    for (int i = 0; i < num; i++)   _elems.push_back(-1);
}

//find an element in the set
int DisjointSets::find(int elem)
{
    //if we are at a -1 node, return the index b/c we are at the root
    if(_elems[elem] < 0)    return elem;
    else                    
    {
        //find the root
        int root = find(_elems[elem]);
        //updates array with new root
        _elems[elem] = root;
        return root;
    }
}

//union by size for two sets
void DisjointSets::setunion(int a, int b)
{
    //gets the two roots
    int root1 = find(a);
    int root2 = find (b);
    //gets new size
    int newSize = _elems[root1] + _elems[root2];

    //makes sure roots are different
    if(root1 != root2)    
    {    
        //if the value at roo1 is less than root2, it is larger
        if(_elems[root1] < _elems[root2])
        {
            //so we merge root 1 with root 2
            _elems[root1] = newSize;
            _elems[root2] = root1;
        }

        //else, do the opposite
        else
        {
            _elems[root2] = newSize;
            _elems[root1] = root2;
        }
    }
}


int DisjointSets::size(int elem)
{
    //gets size 
    int size = -1 * _elems[find(elem)];
    return size;
}/* Your code here! */
