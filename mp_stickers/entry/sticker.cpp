#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");
  StickerSheet mywork(alma, 3);
  mywork.addSticker(i,0,0);
  mywork.addSticker(i,100,100);
  mywork.addSticker(i,200,200);
  Image myImage = mywork.render();
  myImage.writeToFile("myImage.png");
  return 0;
}
