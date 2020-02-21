#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  isFinished_ = true;
  itTrav_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal * t, Point s, PNG i, double tol, bool f)
{
  //assigns members
  itTrav_ = t;
  start_ = s;
  curr_ = s;
  image_ = i;
  tol_ = tol;
  isFinished_ = f;

  //creates 2D visited vector
  isVisited_.resize(image_.width());
  for(unsigned int i = 0; i < isVisited_.size(); i++)
  {
    isVisited_[i].resize(image_.height());
    for(unsigned int j = 0; j < isVisited_[i].size(); j++)
    {
      isVisited_[i][j] = false;
    }
  }  

  //checks if the start point has been visited
  unsigned w = image_.width();
  unsigned h = image_.height();
  HSLAPixel & start = image_.getPixel(start_.x, start_.y); 
  //checks current is in bounds, marks it as visited
  if(curr_.x < w && curr_.y < h)
  {
    isVisited_[curr_.x][curr_.y] = true;
  }
  else
  {
    isFinished_ = true;
  }
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point right(curr_.x + 1, curr_.y);
  Point left(curr_.x - 1, curr_.y);
  Point above(curr_.x, curr_.y - 1);
  Point below(curr_.x, curr_.y + 1);

  //image width and height
  unsigned width = image_.width();
  unsigned height = image_.height();

  //start pixel
  HSLAPixel & startPixel = image_.getPixel(start_.x, start_.y);

  //checks right in bounds
  if(right.x < width && right.y < height)
  {
      //checks right witihin tolerance
      HSLAPixel & rightPixel = image_.getPixel(right.x, right.y);
      if(calculateDelta(startPixel, rightPixel) < tol_)
      {
        //adds to stack/queue
        itTrav_->add(right);
      }
  }

  //checks below in bounds
  if(below.x < width && below.y < height)
  {
      //checks below witihin tolerance
      HSLAPixel & belowPixel = image_.getPixel(below.x, below.y);
      if(calculateDelta(startPixel, belowPixel) < tol_)
      {
        //adds to stack/queue
        itTrav_->add(below);
      }
  }

  //checks right in bounds
  if(below.x < width && below.y < height)
  {
      //checks right witihin tolerance
      HSLAPixel & belowPixel = image_.getPixel(below.x, below.y);
      if(calculateDelta(startPixel, belowPixel) < tol_)
      {
        //adds to stack/queue
        itTrav_->add(below);
      }
  }

  //checks left in bounds
  if(left.x < width && left.y < height)
  {
      //checks left witihin tolerance
      HSLAPixel & leftPixel = image_.getPixel(left.x, left.y);
      if(calculateDelta(startPixel, leftPixel) < tol_)
      {
        //adds to stack/queue
        itTrav_->add(left);
      }
  }
  
  //checks above in bounds
  if(above.x < width && above.y < height)
  {
      //checks right witihin tolerance
      HSLAPixel & abovePixel = image_.getPixel(above.x, above.y);
      if(calculateDelta(startPixel, abovePixel) < tol_)
      {
        //adds to stack/queue
        itTrav_->add(above);
      }
  }

  //if nothing was added to the stack and it's empty, we are finished with the traversal
  if(itTrav_->empty() == true)
  {
    isFinished_ = true;
    return *this;
  }

  //to find the next node to traverse, we need to find the first unvisited node in the stack/queue
  Point next;
  //we set next = to the popped value from the stack/queue
  do{
    next = itTrav_->pop();
    //however, if the stack/queue is empty we have nothing to pop, and the traversal is finished
    if(itTrav_->empty())
    {
      isFinished_ = true;
      return *this;
    }
  }while (isVisited_[next.x][next.y] == true); //keep looping while the next point has already been visited

  //once we have found the first unvisited node, we set it as the current node in the traversal and mark it as visited
  isVisited_[next.x][next.y] = true;
  curr_ = next;

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return ((this->isFinished_ == other.isFinished_) ? false : true);
}