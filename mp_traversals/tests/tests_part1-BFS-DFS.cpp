#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <deque>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "ImageTraversal.h"

using namespace cs225;

TEST_CASE("DFS maintains the deepest point on top", "[weight=1][part=1][part=1a]") {
  std::deque<Point> work_list;

  Traversals::dfs_add( work_list, Point(20, 20) );
  Traversals::dfs_add( work_list, Point(2, 2) );
  Traversals::dfs_add( work_list, Point(2, 3) );
  Traversals::dfs_add( work_list, Point(2, 4) );

  REQUIRE( Traversals::dfs_pop(work_list) == Point(2, 4) );
}

TEST_CASE("DFS maintains a depth-first ordering", "[weight=1][part=1][part=1a]") {
  std::deque<Point> work_list;

  Traversals::dfs_add( work_list, Point(20, 20) );
  Traversals::dfs_add( work_list, Point(2, 2) );
  Traversals::dfs_add( work_list, Point(2, 3) );
  Traversals::dfs_add( work_list, Point(2, 4) );

  REQUIRE( Traversals::dfs_pop(work_list) == Point(2, 4) );
  REQUIRE( Traversals::dfs_pop(work_list) == Point(2, 3) );
  REQUIRE( Traversals::dfs_pop(work_list) == Point(2, 2) );
  REQUIRE( Traversals::dfs_pop(work_list) == Point(20, 20) );
}

TEST_CASE("BFS maintains the correct point on top", "[weight=1][part=1][part=1b]") {
  std::deque<Point> work_list;

  Traversals::bfs_add( work_list, Point(20, 20) );
  Traversals::bfs_add( work_list, Point(2, 2) );
  Traversals::bfs_add( work_list, Point(2, 3) );
  Traversals::bfs_add( work_list, Point(2, 4) );

  REQUIRE( Traversals::bfs_pop(work_list) == Point(20, 20) );
}

TEST_CASE("BFS maintains the BFS ordering", "[weight=1][part=1][part=1b]") {
  std::deque<Point> work_list;

  Traversals::bfs_add( work_list, Point(20, 20) );
  Traversals::bfs_add( work_list, Point(2, 2) );
  Traversals::bfs_add( work_list, Point(2, 3) );
  Traversals::bfs_add( work_list, Point(2, 4) );

  REQUIRE( Traversals::bfs_pop(work_list) == Point(20, 20) );
  REQUIRE( Traversals::bfs_pop(work_list) == Point(2, 2) );
  REQUIRE( Traversals::bfs_pop(work_list) == Point(2, 3) );
  REQUIRE( Traversals::bfs_pop(work_list) == Point(2, 4) );
}
