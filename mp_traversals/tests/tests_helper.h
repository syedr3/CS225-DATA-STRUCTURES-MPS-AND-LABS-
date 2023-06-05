/**
 * @file tests_helper.h
 */
#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

/**
 * Returns a 4x4 image with a white center and black border:
 * 
 *     X X X X
 *     X - - X       X: black
 *     X - - X       -: white
 *     X X X X
 * 
 * The black/X (h=180, s=1, l=0) is as different from
 * white/- (h=0, s=0, l=1) as possible.
**/
PNG getTestPNG();

/**
 *     0 1 2 3 4 5 6 7 
 *   -----------------
 *  0: X X X X X X X X
 *  1: X - - - - - - X    X: black
 *  2: X - * - - X - X    -: white
 *  3: X X X X X X X X    *: Starting point (white)
 * 
 * The black/X (h=180, s=1, l=0) is as different from
 * white/- (h=0, s=0, l=1) as possible.
**/
PNG getTestPNG_8x4();