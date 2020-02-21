/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
  HSLAPixel::HSLAPixel(){
    //default constructor implementation for HSLAPixel with non-transparent, white, alpha = 1.0 pixel
    l = 1;  // if luminance is 1, hue and saturation don't matter and it's just white/black
    a = 1;  // alpha value of 1 makes the pixel opaque
  }
  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
    //parameterized constructor for HSLAPixe; implementation with hue, saturation, and luminance values

    // set hsl values to the user provided parameters
    h = hue;
    s = saturation;
    l = luminance;
    a = 1;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
    // fully parameterized constructor for HSLAPixel; implementation with HSL and with alpha value

    // set hsla values to the user provided parameters
    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
    }


}
