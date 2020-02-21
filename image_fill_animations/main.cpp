
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG toFill;      
  toFill.readFromFile("tests/pacman.png");

  FloodFilledImage ffig = FloodFilledImage(toFill);
  ImageTraversal * dfs = new DFS(toFill, Point(100, 50), 0.21111333);
  ImageTraversal * bfs = new BFS(toFill, Point(100, 50), 0.23568190);
  HSLAPixel lightgreen = HSLAPixel(89, .46, .48, 1);
  HSLAPixel lightblue = HSLAPixel(199, .92, .56, 1);
  HSLAPixel indigo = HSLAPixel(231, .48, .48, 1);
  HSLAPixel purple = HSLAPixel(291, .47, .6, 1);

  ColorPicker * cp1 = new MyColorPicker(lightgreen, lightblue, indigo, purple, Point(100, 50));
  ColorPicker * cp2 = new RainbowColorPicker(0.1);

  ffig.addFloodFill(*dfs, *cp1);
  ffig.addFloodFill(*bfs, *cp2);

  Animation animation = ffig.animate(10000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
