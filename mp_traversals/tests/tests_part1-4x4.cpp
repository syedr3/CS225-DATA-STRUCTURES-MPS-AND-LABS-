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
 * getTestPNG() method returns a 4x4 image with a white center and black border:
 * 
 *     X X X X
 *     X - - X       X: black
 *     X - - X       -: white
 *     X X X X
 * 
 * The black/X (h=180, s=1, l=0) is as different from
 * white/- (h=0, s=0, l=1) as possible.
 * It is defined in tests_helper.h/cpp
**/

TEST_CASE("DFS iterator starts at the start point", "[weight=2][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  Traversals::ImageTraversal dfs(png, startPoint, 0.2, Traversals::dfs_add, Traversals::dfs_pop);
  REQUIRE( *(dfs.begin()) == startPoint );
}

TEST_CASE("DFS visits the correct pixel first", "[weight=2][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  Traversals::ImageTraversal dfs(png, startPoint, 0.2, Traversals::dfs_add, Traversals::dfs_pop);
  Traversals::ImageTraversal::Iterator it = dfs.begin();
  ++it;
  REQUIRE( *it == Point(1, 2) );
}


TEST_CASE("BFS iterator starts at the start point", "[weight=2][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  Traversals::ImageTraversal bfs(png, startPoint, 0.2, Traversals::bfs_add, Traversals::bfs_pop);
  REQUIRE( *(bfs.begin()) == startPoint );
}

TEST_CASE("BFS visits the correct pixel first", "[weight=2][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  Traversals::ImageTraversal bfs(png, startPoint, 0.2, Traversals::bfs_add, Traversals::bfs_pop);
  Traversals::ImageTraversal::Iterator it = bfs.begin();
  ++it;
  REQUIRE( *it == Point(2, 1) );
}


TEST_CASE("DFS visits all points within a tolerance", "[weight=1][part=1][valgrind]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  Traversals::ImageTraversal t(png, startPoint, 0.2, Traversals::dfs_add, Traversals::dfs_pop);
  unsigned count = 0;
  for (const Point & p : t) {
    count++;
  }
  REQUIRE( count == 4 );
}

TEST_CASE("BFS visits all points within a tolerance", "[weight=1][part=1][valgrind]") {
  PNG png = getTestPNG();
  Point startPoint(1, 1);
  
  Traversals::ImageTraversal t(png, startPoint, 0.2, Traversals::bfs_add, Traversals::bfs_pop);
  unsigned count = 0;
  for (const Point & p : t) {
    count++;
  }
  REQUIRE( count == 4 );
}


TEST_CASE("DFS visits all points within a tolerance (includes pixels on image edge)", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  Traversals::ImageTraversal t(png, startPoint, 0.2, Traversals::dfs_add, Traversals::dfs_pop);
  unsigned count = 0;
  for (const Point & p : t) { count++; }

  REQUIRE( count == 12 );
}

TEST_CASE("BFS visits all points within a tolerance (includes pixels on image edge)", "[weight=1][part=1]") {
  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  Traversals::ImageTraversal t(png, startPoint, 0.2, Traversals::bfs_add, Traversals::bfs_pop);
  unsigned count = 0;
  for (const Point & p : t) { count++; }

  REQUIRE( count == 12 );
}


TEST_CASE("DFS iterator visits all points in the correct order", "[weight=1][part=1][valgrind]") {
  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  Traversals::ImageTraversal t(png, startPoint, 0.2, Traversals::dfs_add, Traversals::dfs_pop);
  Traversals::ImageTraversal::Iterator it = t.begin();

  REQUIRE( *it == Point(0, 0) ); ++it;
  REQUIRE( *it == Point(0, 1) ); ++it;
  REQUIRE( *it == Point(0, 2) ); ++it;
  REQUIRE( *it == Point(0, 3) ); ++it;
  REQUIRE( *it == Point(1, 3) ); ++it;
  REQUIRE( *it == Point(2, 3) ); ++it;  
  REQUIRE( *it == Point(3, 3) ); ++it;
  REQUIRE( *it == Point(3, 2) ); ++it;
  REQUIRE( *it == Point(3, 1) ); ++it;  
  REQUIRE( *it == Point(3, 0) ); ++it;
  REQUIRE( *it == Point(2, 0) ); ++it;
  REQUIRE( *it == Point(1, 0) ); ++it;  
}

TEST_CASE("BFS iterator visits all points in the correct order", "[weight=1][part=1][valgrind]") {
  PNG png = getTestPNG();
  Point startPoint(0, 0);
  
  Traversals::ImageTraversal t(png, startPoint, 0.2, Traversals::bfs_add, Traversals::bfs_pop);
  Traversals::ImageTraversal::Iterator it = t.begin();

  REQUIRE( *it == Point(0, 0) ); ++it;

  REQUIRE( *it == Point(1, 0) ); ++it;  
  REQUIRE( *it == Point(0, 1) ); ++it;

  REQUIRE( *it == Point(2, 0) ); ++it;  
  REQUIRE( *it == Point(0, 2) ); ++it;

  REQUIRE( *it == Point(3, 0) ); ++it;
  REQUIRE( *it == Point(0, 3) ); ++it;

  REQUIRE( *it == Point(3, 1) ); ++it;
  REQUIRE( *it == Point(1, 3) ); ++it;
  
  REQUIRE( *it == Point(3, 2) ); ++it;
  REQUIRE( *it == Point(2, 3) ); ++it;

  REQUIRE( *it == Point(3, 3) ); ++it;
}
