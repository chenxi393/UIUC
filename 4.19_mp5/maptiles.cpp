/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* Mosaic=new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> Buildtree;
    map<Point<3>, int> tile_avg_map;
    //unordered_map 哈希表
    for(unsigned i=0;i<theTiles.size();i++){
        HSLAPixel temp=theTiles[i].getAverageColor();
        Point<3>temp2=convertToLAB(temp);
        Buildtree.push_back(temp2);
        tile_avg_map[temp2]=i;
    }
    KDTree<3> tree_(Buildtree);
    for(int i=0;i<theSource.getRows();i++){
        for(int j=0;j<theSource.getColumns();j++){
            Mosaic->setTile(i,j,get_match_at_idx(tree_,tile_avg_map,theTiles,theSource,i,j));
        }
    }
    return Mosaic;
}

//map<Point<3>, int> 
//map<key,value>//红黑树实现的

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
