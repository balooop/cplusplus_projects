#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <queue>
#include <vector>
#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  floodFilled_ = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  //push addresses to traversal, b/c we have vectors of pointers
  trav_.push_back(&traversal);
  cp_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  
  //algorithm:
  //define a temporary image to be modified for the animation
  //loop through all traversals in the array
  //loop through all points in each traversal
  //if we are at an interval to be captured, we capture it (iteration % interval)
  //if we are not, we change the colors
  //after each traversal, we capture the final frme.
  //move to next traversal

  PNG frame = floodFilled_;

  unsigned frameCount = 0;
  
  for(unsigned i = 0; i < trav_.size(); i++){

    for (const Point & p : *(trav_.at(i))) {
      
      //grabs base and picked pixel
      HSLAPixel & basePixel = frame.getPixel(p.x, p.y); 
      HSLAPixel cpPixel = cp_.at(i)->getColor(p.x, p.y);
      
      //we capture after every four pixels are colored
      if(frameCount % frameInterval == 0){
        animation.addFrame(frame);
      }

      //if it isn't a capture point, we modify another pixel
      //modifies base image pixel to be color picked pixel
      basePixel.h = cpPixel.h;
      basePixel.s = cpPixel.s;
      basePixel.l = cpPixel.l;
      basePixel.a = cpPixel.a;
      
      //increments count of
      frameCount++;
    }
    //capture the finished state of each traversal
    animation.addFrame(frame);
  }
  return animation;
}
