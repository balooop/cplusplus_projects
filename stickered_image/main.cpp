#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  
  //reads basae image
  Image base;
  base.readFromFile("alma.png");
  //creates stickersheet
  StickerSheet myStickers = StickerSheet(base, 5);

  Image sticker1, sticker2, sticker3, sticker4;
  //reads stickers from files
  sticker1.readFromFile("sticker1.png");
  sticker2.readFromFile("sticker2.png");
  sticker3.readFromFile("sticker3.png");
  sticker4.readFromFile("sticker4.png");

  //adds stickers to my sheet
  myStickers.addSticker(sticker1, 420, 14);
  myStickers.addSticker(sticker2, 562, 65);
  myStickers.addSticker(sticker2, 310, 65);
  myStickers.addSticker(sticker3, 460, 325);
  myStickers.addSticker(sticker4, 360, 325);

  //renders and saves image
  Image renderedImage = myStickers.render();
  renderedImage.writeToFile("myImage.png");
  return 0;
}
