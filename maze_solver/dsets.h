/* Your code here! */
#pragma once

#include <stdint.h>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

class DisjointSets
{
    private:
        //vector of ints representing uptrees
        std::vector<int> _elems;
    public:
        //add an unconnected root node to the vector
        void addelements(int num);
        //find an element in the disjoiint sets
        int find(int elem);
        //union-by-size for two sets
        void setunion(int a, int b);
        //gets number of nodes in the uptree with elem
        int size(int elem);
};