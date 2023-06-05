/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

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
    MosaicCanvas* map_Tiles = new MosaicCanvas (theSource.getRows(), theSource.getColumns());
    vector<Point<3>> color;
    map<Point<3>, TileImage*> colormap;
    unsigned long x = 0;
    while (x != theTiles.size()){
        color.push_back(convertToXYZ(theTiles[x].getAverageColor()));
        colormap[convertToXYZ(theTiles[x].getAverageColor())] = &theTiles[x];
        x++;
    }
    KDTree<3> PLZ_WORK(color);
    for (int i = 0; i < theSource.getRows(); i++){
        for (int j = 0; j < theSource.getColumns(); j++){
            Point<3> original_color = convertToXYZ(theSource.getRegionColor(i,j));
            Point<3> mosaic_color = PLZ_WORK.findNearestNeighbor(original_color);
            map_Tiles->setTile(i,j,colormap[mosaic_color]);
        }
    }
    return map_Tiles;
}

