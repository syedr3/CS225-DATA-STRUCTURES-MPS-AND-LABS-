#include <catch2/catch_test_macros.hpp>

#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

static void checkStickerPlacement(const Image& sticker, const Image& sheet, const int& xOffset, const int& yOffset) {
  for (size_t x = 0; x < sticker.width(); ++x) {
    for (size_t y = 0; y < sticker.height(); ++y) {
      const HSLAPixel &stickerPixel = sticker.getPixel(x, y);
      const HSLAPixel &sheetPixel = sheet.getPixel(x + xOffset, y + yOffset);
      REQUIRE( (stickerPixel.a == 1 ? stickerPixel == sheetPixel : true) );
    }
  }
}

TEST_CASE("A basic StickerSheet works", "[weight=5][part=2][valgrind][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");
  StickerSheet sheet(alma, 5);
  REQUIRE( sheet.layers() == 5);
  sheet.addSticker(i, 20, 200);
  Image expected;
  expected.readFromFile("../data/expected.png");
  REQUIRE( sheet.render() == expected );
}

TEST_CASE("A StickerSheet with no stickers works", "[weight=5][part=2][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");

  StickerSheet sheet(alma, 5);
  REQUIRE( sheet.layers() == 5);

  REQUIRE( sheet.render() == alma );
}


TEST_CASE("StickerSheet does not duplicate stickers in memory", "[weight=5][part=2][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  REQUIRE( sheet.getSticker(0) == &i );
}

TEST_CASE("StickerSheet behaves correctly when a sticker is updated", "[weight=5][part=2][timeout=30000]") {
  Image alma;    alma.readFromFile("../data/alma.png");
  Image i;       i.readFromFile("../data/i.png");
  Image penguin; penguin.readFromFile("../data/penguin.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  i = penguin;

  checkStickerPlacement(penguin, sheet.render(), 20, 200);
}

TEST_CASE("StickerSheet::addSticker() adds a new layer when sheet is full", "[weight=5][part=2][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 2);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 60, 200);

  REQUIRE(sheet.layers() == 2);
  REQUIRE(sheet.addSticker(i, 100, 200) == 2); 
  REQUIRE(sheet.layers() == 3);

  Image expected;
  expected.readFromFile("../data/expected-5.png");

  REQUIRE( sheet.render() == expected );
}

//
// test setStickerAtLayer
//
TEST_CASE("StickerSheet::setStickerAtLayer() adds to the correct layer", "[weight=5][part=2][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");
  // Image penguin;    penguin.readFromFile("../data/penguin.png");

  StickerSheet sheet(alma, 3);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 140, 200);
  sheet.addSticker(i, 100, 200);
  
  REQUIRE(sheet.setStickerAtLayer(i, 1, 60, 200) == 1);
  REQUIRE(sheet.layers() == 3);

  Image expected;
  expected.readFromFile("../data/expected-5.png");

  REQUIRE( sheet.render() == expected );

}

TEST_CASE("StickerSheet::setStickerAtLayer() fails for an invalid layer", "[weight=5][part=2][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");
  // Image penguin;    penguin.readFromFile("../data/penguin.png");

  StickerSheet sheet(alma, 3);

  REQUIRE(sheet.setStickerAtLayer(i, 3, 60, 200) == -1);
  REQUIRE( sheet.render() == alma );
}

//
// test changeMaxStickers
//
TEST_CASE("StickerSheet::changeMaxStickers() can increase the number of stickers on an image", "[weight=1][part=2][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 1);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(2);
  REQUIRE(sheet.layers() == 2);
  sheet.addSticker(i, 40, 200);

  Image expected;
  expected.readFromFile("../data/expected-2.png");

  REQUIRE( sheet.render() == expected );
}


TEST_CASE("StickerSheet::changeMaxStickers() does not discard stickers when resized larger", "[weight=1][part=2][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(7);

  Image expected;
  expected.readFromFile("../data/expected.png");

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::changeMaxStickers() does not discard original stickers when resized smaller", "[weight=1][part=2][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(3);

  Image expected;
  expected.readFromFile("../data/expected.png");

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::changeMaxStickers() discards stickers beyond the end of a smaller StickerSheet", "[weight=1][part=2][valgrind][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.changeMaxStickers(1);

  REQUIRE( sheet.render() == expected );
}

//
// test removeSticker
//
TEST_CASE("StickerSheet::removeSticker() can remove the last sticker", "[weight=1][part=2][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 50, 200);
  sheet.removeSticker(1);

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::removeSticker() can remove the first sticker", "[weight=1][part=2][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.addSticker(i, 20, 200);
  sheet.removeSticker(0);

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::removeSticker() can remove all stickers", "[weight=1][part=2][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 80, 200);
  sheet.removeSticker(2);
  sheet.removeSticker(1);
  sheet.removeSticker(0);

  REQUIRE( sheet.render() == alma );
}

//
// test that getSticker works
//
TEST_CASE("StickerSheet::getSticker() returns the sticker", "[weight=1][part=2][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);

  REQUIRE( *(sheet.getSticker(0)) == i );
}

TEST_CASE("StickerSheet::getSticker() returns NULL for a non-existant sticker", "[weight=1][part=2][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);

  REQUIRE( sheet.getSticker(1) == NULL );
}

TEST_CASE("StickerSheet::getSticker() returns NULL for a removed sticker", "[weight=1][part=2][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.removeSticker(0);

  REQUIRE( sheet.getSticker(0) == NULL );
}

//
// translate
//
TEST_CASE("StickerSheet::translate() translates a sticker's location", "[weight=1][part=2][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 0, 0);
  sheet.translate(0, 20, 200);

  REQUIRE( sheet.render() == expected );
}

TEST_CASE("StickerSheet::translate() returns false for a non-existant sticker", "[weight=1][part=2][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  REQUIRE( sheet.translate(3, 20, 200) == false );
}

//
// render
//
TEST_CASE("A complex StickerSheet is correct", "[weight=5][part=2][timeout=30000]") {
  Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected-3.png");

  StickerSheet sheet(alma, 100);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.addSticker(i, 80, 200);
  sheet.addSticker(i, 100, 200);
  sheet.addSticker(i, 120, 200);
  sheet.addSticker(i, 140, 200);
  sheet.removeSticker(3);
  sheet.translate(0, 0, 0);

  REQUIRE( sheet.render() == expected );
}

//
// copy ctor
//
TEST_CASE("StickerSheet's copy constructor makes an independent copy", "[weight=2][part=2][valgrind][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");
  Image expected2; expected2.readFromFile("../data/expected-2.png");

  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(s1);
  s2.removeSticker(1);

  REQUIRE( s1.render() == expected2 );
  REQUIRE( s2.render() == expected );
}

TEST_CASE("StickerSheet's assignment operator makes an independent copy", "[weight=2][part=2][valgrind][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected.png");
  Image expected2; expected2.readFromFile("../data/expected-2.png");

  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(alma, 5);
  s2 = s1;
  s2.removeSticker(1);

  REQUIRE( s1.render() == expected2 );
  REQUIRE( s2.render() == expected );
}


//
// out of bounds with sanity checks
//

 TEST_CASE("A StickerSheet with stickers at negative coordinates works", "[weight=5][part=2][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 1);
  sheet.addSticker(i, -42, -225);

  Image render = sheet.render();

  REQUIRE( render.width() == alma.width() + 42 );
  REQUIRE( render.height() == alma.height() + 225 );

  checkStickerPlacement(i, render, 0, 0);
  Image expected;
  expected.readFromFile("../data/expected-6.png");

  REQUIRE( render == expected );

}

TEST_CASE("A StickerSheet with stickers placed beyond base image boundaries works", "[weight=5][part=2][valgrind][timeout=30000]") {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma, 5);

  /**
   * For testing deep copy of base image
   * The {...} are used for a block statement
   * and are intentional
   */
  {
    Image almaDuplicate = alma;

    StickerSheet sheetDuplicate(almaDuplicate, 5);
    sheet = sheetDuplicate;
  }

  sheet.addSticker(i, 800, 200);
  sheet.addSticker(i, 50, 500);

  sheet.changeMaxStickers(7);
  sheet.removeSticker(1);
  sheet.changeMaxStickers(4);

  const Image &renderXBound = sheet.render();

  REQUIRE( renderXBound.width() == i.width() + 800 );
  REQUIRE( renderXBound.height() == alma.height() );

  checkStickerPlacement(i, renderXBound, 800, 200);

  sheet.removeSticker(0);

  REQUIRE( sheet.render() == alma );

  sheet.addSticker(i, 20, 500);
  sheet.changeMaxStickers(1);

  const Image &renderYBound = sheet.render();

  REQUIRE( renderYBound.width() == alma.width() );
  REQUIRE( renderYBound.height() == i.height() + 500 );

  checkStickerPlacement(i, renderYBound, 20, 500);

  sheet.removeSticker(0);
  sheet.changeMaxStickers(2);

  REQUIRE( sheet.render() == alma );

  sheet.addSticker(i, 800, 200);
  sheet.addSticker(i, -100, -500);

  const Image &renderXYBound = sheet.render();

  checkStickerPlacement(i, renderXYBound, 900, 700);
  checkStickerPlacement(i, renderXYBound, 0, 0);

  sheet.changeMaxStickers(0);

  REQUIRE( sheet.render() == alma );
}

