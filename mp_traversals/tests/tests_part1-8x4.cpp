#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "ImageTraversal.h"
#include "tests_helper.h"

using namespace cs225;

/**
 * getTestPNG_8x4() method returns a 8x4 image as follows:
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

TEST_CASE("DFS iterator visits all points in the correct order (8x4 image)", "[weight=1][part=1]") {
  PNG png = getTestPNG_8x4();
  Point startPoint(2, 2);
  
  Traversals::ImageTraversal t(png, startPoint, 0.2, Traversals::dfs_add, Traversals::dfs_pop);
  Traversals::ImageTraversal::Iterator it = t.begin();

  REQUIRE( *it == Point(2, 2) ); ++it; 
  REQUIRE( *it == Point(2, 1) ); ++it;

  REQUIRE( *it == Point(1, 1) ); ++it;
  REQUIRE( *it == Point(1, 2) ); ++it;

  REQUIRE( *it == Point(3, 1) ); ++it;
  REQUIRE( *it == Point(3, 2) ); ++it;

  REQUIRE( *it == Point(4, 2) ); ++it;
  REQUIRE( *it == Point(4, 1) ); ++it;

  REQUIRE( *it == Point(5, 1) ); ++it;

  REQUIRE( *it == Point(6, 1) ); ++it;
  REQUIRE( *it == Point(6, 2) ); ++it;
}

TEST_CASE("BFS iterator visits all points in the correct order (8x4 image)", "[weight=1][part=1]") {
  PNG png = getTestPNG_8x4();
  Point startPoint(2, 2);
  
  Traversals::ImageTraversal t(png, startPoint, 0.2, Traversals::bfs_add, Traversals::bfs_pop);
  Traversals::ImageTraversal::Iterator it = t.begin();

  REQUIRE( *it == Point(2, 2) ); ++it;

  REQUIRE( *it == Point(3, 2) ); ++it;  
  REQUIRE( *it == Point(1, 2) ); ++it;
  REQUIRE( *it == Point(2, 1) ); ++it;

  REQUIRE( *it == Point(4, 2) ); ++it;
  REQUIRE( *it == Point(3, 1) ); ++it;

  REQUIRE( *it == Point(1, 1) ); ++it;

  REQUIRE( *it == Point(4, 1) ); ++it;
  REQUIRE( *it == Point(5, 1) ); ++it;
  REQUIRE( *it == Point(6, 1) ); ++it;
  REQUIRE( *it == Point(6, 2) ); ++it;
}
