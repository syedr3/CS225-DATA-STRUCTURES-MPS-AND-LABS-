#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "Animation.h"
#include "FloodFilledImage.h"

#include "ImageTraversal.h"

#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;


TEST_CASE("Illini I - FloodFilledImage - DFS", "[weight=3][part=2]") {
  PNG png;       png.readFromFile("../data/i.png");
  PNG expected;  expected.readFromFile("../data/i-rainbow-dfs.png");
  PNG expected2; expected2.readFromFile("../data/i-rainbow-dfs-2.png");
  
  FloodFilledImage image(png);
  Traversals::ImageTraversal dfs(png, Point(40, 40), 0.05, Traversals::dfs_add, Traversals::dfs_pop);
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill( dfs, rainbow );

  Animation animation = image.animate(1000);
  
  REQUIRE( animation.frameCount() > 2 );
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  secondFrame.writeToFile("i-rainbow-dfs-2.png");
  lastFrame.writeToFile("i-rainbow-dfs.png");
  animation.write("i-rainbow-dfs.gif");
  INFO("Files written to i-rainbow-dfs-* for debugging.");
  
  REQUIRE( secondFrame == expected2 );
  REQUIRE( lastFrame == expected );
}

TEST_CASE("Illini I - FloodFilledImage - BFS", "[weight=3][part=2]") {
  PNG png;      png.readFromFile("../data/i.png");
  PNG expected; expected.readFromFile("../data/i-rainbow-bfs.png");
  PNG expected2; expected2.readFromFile("../data/i-rainbow-bfs-2.png");
  
  FloodFilledImage image(png);
  Traversals::ImageTraversal bfs(png, Point(40, 40), 0.05, Traversals::bfs_add, Traversals::bfs_pop);
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill( bfs, rainbow );

  Animation animation = image.animate(1000);

  REQUIRE( animation.frameCount() > 2 );
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  secondFrame.writeToFile("i-rainbow-bfs-2.png");
  lastFrame.writeToFile("i-rainbow-bfs.png");
  animation.write("i-rainbow-bfs.gif");
  INFO("Files written to i-rainbow-bfs-* for debugging.");
  
  REQUIRE( secondFrame == expected2 );
  REQUIRE( lastFrame == expected );
}


TEST_CASE("Lantern - FloodFilledImage - BFS", "[weight=3][part=2]") {
  PNG png;      png.readFromFile("../data/lantern.png");
  PNG expected; expected.readFromFile("../data/lantern-rainbow-bfs.png");
  PNG expected2; expected2.readFromFile("../data/lantern-rainbow-bfs-2.png");
  
  FloodFilledImage image(png);
  Traversals::ImageTraversal bfs(png, Point(40, 40), 0.5, Traversals::bfs_add, Traversals::bfs_pop);
  RainbowColorPicker rainbow(0.5);
  image.addFloodFill( bfs, rainbow );

  Animation animation = image.animate(1000);

  REQUIRE( animation.frameCount() > 2 );
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  secondFrame.writeToFile("lantern-rainbow-bfs-2.png");
  lastFrame.writeToFile("lantern-rainbow-bfs.png");
  animation.write("lantern-rainbow-bfs.gif");
  INFO("Files written to lantern-rainbow-bfs-* for debugging.");
  
  REQUIRE( secondFrame == expected2 );
  REQUIRE( lastFrame == expected );
}


TEST_CASE("PacMan - FloodFilledImage - DFS", "[weight=3][part=2][valgrind][timeout=45000]") {
  PNG png;      png.readFromFile("../data/pacman.png");
  PNG expected; expected.readFromFile("../data/pacman-solid-dfs.png");
  PNG expected2; expected2.readFromFile("../data/pacman-solid-dfs-2.png");
  
  FloodFilledImage image(png);
  Traversals::ImageTraversal dfs(png, Point(100, 50), 0.2, Traversals::dfs_add, Traversals::dfs_pop);
  HSLAPixel color(231, 1, 0.5);
  SolidColorPicker solid(color);
  image.addFloodFill( dfs, solid );

  Animation animation = image.animate(1000);

  REQUIRE( animation.frameCount() > 2 );
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  secondFrame.writeToFile("pacman-solid-dfs-2.png");
  lastFrame.writeToFile("pacman-solid-dfs.png");
  animation.write("pacman-solid-dfs.gif");
  INFO("Files written to pacman-solid-dfs-* for debugging.");
  
  REQUIRE( secondFrame == expected2 );
  REQUIRE( lastFrame == expected );
}

TEST_CASE("PacMan - FloodFilledImage - BFS", "[weight=3][part=2][valgrind][timeout=45000]") {
  PNG png;      png.readFromFile("../data/pacman.png");
  PNG expected; expected.readFromFile("../data/pacman-solid-bfs.png");
  PNG expected2; expected2.readFromFile("../data/pacman-solid-bfs-2.png");
  
  FloodFilledImage image(png);
  Traversals::ImageTraversal bfs(png, Point(100, 50), 0.2, Traversals::bfs_add, Traversals::bfs_pop);
  HSLAPixel color(231, 1, 0.5);
  SolidColorPicker solid(color);
  image.addFloodFill( bfs, solid );

  Animation animation = image.animate(1000);

  REQUIRE( animation.frameCount() > 2 );
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  secondFrame.writeToFile("pacman-solid-bfs-2.png");
  lastFrame.writeToFile("pacman-solid-bfs.png");
  animation.write("pacman-solid-bfs.gif");
  INFO("Files written to pacman-solid-bfs-* for debugging.");

  REQUIRE( secondFrame == expected2 );
  REQUIRE( lastFrame == expected );
}
