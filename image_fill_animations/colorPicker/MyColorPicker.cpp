#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(HSLAPixel c1, HSLAPixel c2, HSLAPixel c3, HSLAPixel c4, Point c)
{
  color1 = c1;
  color2 = c2;
  color2 = c2;
  color2 = c2;
  xCenter = c;
}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double dx = x - xCenter.x;

  if (dx >= 1) { return color4; }

  double h = color1.h - (color1.h * dx) + (color2.h * dx) + (color3.h * dx) + (color4.h * dx);
  double s = color1.s - (color1.s * dx) + (color2.s * dx) + (color3.s * dx) + (color4.s * dx);
  double l = color1.l- (color1.l * dx) + (color2.l * dx) + (color3.l * dx) + (color4.l * dx);

  return HSLAPixel(h, s, l);
  return HSLAPixel();
}
