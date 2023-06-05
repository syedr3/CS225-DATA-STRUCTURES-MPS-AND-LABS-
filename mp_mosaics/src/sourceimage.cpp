/**
 * sourceimage.cpp (v2)
 *
 * SourceImage extends the Image class and provides some additional data and
 * functions suitable for the source image for the photomosaic.  The default
 * constructor will take a number of rows and columns to divide the image
 * into.  The image will then be processes to find the average color of each
 * region.
 *
 * @authors
 * Wade Fagen-Ulmschneider (http://waf.cs.illinois.edu/)
 * Jack Toole
 * Matt Sachtler
 * Scott Wegner
 *
 * @date Fall 2017
 */

#include <algorithm>
#include <cmath>
#include <iostream>

#include "sourceimage.h"

using namespace std;

SourceImage::SourceImage(const PNG& image, int setResolution)
    : backingImage(image), resolution(setResolution)
{
    if (resolution < 1) {
        cerr << "ERROR: resolution set to < 1. Aborting." << endl;
        exit(-1);
    }

    resolution = min(backingImage.width(), backingImage.height());
    resolution = min(resolution, setResolution);
}

LUVAPixel SourceImage::getRegionColor(int row, int col) const {
    int width = backingImage.width();
    int height = backingImage.height();

    int startX = divide(width * col,        getColumns());
    int endX   = divide(width * (col + 1),  getColumns());
    int startY = divide(height * row,       getRows());
    int endY   = divide(height * (row + 1), getRows());

    //double h_sin = 0, h_cos = 0, s = 0, l = 0;
    double sumX = 0, sumY = 0, sumZ = 0;

    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            sumX += backingImage.getPixel(x, y).l;
            sumY += backingImage.getPixel(x, y).u;
            sumZ += backingImage.getPixel(x, y).v;
        }
    }

    double numPixels = (endX - startX) * (endY - startY);
    return LUVAPixel( sumX / numPixels, sumY / numPixels, sumZ / numPixels );
}

int SourceImage::getRows() const {
    if (backingImage.height() <= backingImage.width())
        return resolution;
    else
        return divide(resolution * backingImage.height(), backingImage.width());
}

int SourceImage::getColumns() const {
    if (backingImage.width() <= backingImage.height())
        return resolution;
    else
        return divide(resolution * backingImage.width(), backingImage.height());
}

uint64_t SourceImage::divide(uint64_t a, uint64_t b) {
    return (a + b / 2) / b;
}
