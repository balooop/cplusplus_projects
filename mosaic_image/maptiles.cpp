/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    //rows and columns of source image
    unsigned r = theSource.getRows();
    unsigned c = theSource.getColumns();
    //allocates new mosaic on the heap
    MosaicCanvas * my_mosaic = new MosaicCanvas(r, c);

    //map to store pair of color and tile for each tile
    std::map<Point<3>, TileImage*> mosaic_map;
    //vector to store color points to put in KD Tree
    vector<Point<3>> color_tree_vector;

    //populates vector for KD tree construction with average color point for each tile
    //populates map with key value pairs of the average color point and correspoding tile
    for(unsigned cur_idx = 0; cur_idx < theTiles.size(); cur_idx++)
    {
        //gets current tile
        // TileImage cur_tile = theTiles[cur_idx];
        //average color of current tile
        LUVAPixel avg_color = theTiles[cur_idx].getAverageColor();
        //converts color to point for KD Tree
        Point<3> avg_color_point = convertToXYZ(avg_color);
        //pushes point to vector
        color_tree_vector.push_back(avg_color_point);
        //creates a pair of avg color and tile for the map
        std::pair<Point<3>, TileImage *> tile_color_pair = std::pair<Point<3>, TileImage *>(avg_color_point, &theTiles[cur_idx]);
        //pushes pair to map
        mosaic_map.insert(tile_color_pair);
    }

    //constrcuts KD tree from tree of color points created
    KDTree<3> color_tree = KDTree<3>(color_tree_vector);

    for(unsigned row = 0; row < r; row++)
    {
        for(unsigned col = 0; col < c; col++)
        {
            //gets color at source image
            LUVAPixel src_color = theSource.getRegionColor(row, col);
            //converts source color to xyz point
            Point<3> src_color_point = convertToXYZ(src_color);
            //finds nearest neighbour in kd color tree to source color
            Point<3> nearest_color = color_tree.findNearestNeighbor(src_color_point);
            //getts tile to be mapped based on color key
            TileImage * map_tile = mosaic_map[nearest_color];
            //sets tile on mosaic
            my_mosaic->setTile(row, col, map_tile); 
        }
    }
    return my_mosaic;
}
