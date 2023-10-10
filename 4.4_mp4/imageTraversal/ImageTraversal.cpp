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
    pp=NULL;
    curr=Point(-1,-1);
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
    if(pp->empty()){
        curr=Point(-1,-1);
        return *this;
    }
    curr=pp->pop();
    pp->visited[curr.x][curr.y] = true;
    Point p1(curr.x + 1, curr.y);
    Point p2(curr.x, curr.y + 1);
    Point p3(curr.x - 1, curr.y);
    Point p4(curr.x, curr.y - 1);
    const PNG &png_=pp->png_;
    const double tolerance_=pp->tolerance_;
    bool **visited=pp->visited;
    if (p1.x < pp->png_.width() && calculateDelta(*png_.getPixel(curr.x, curr.y), *png_.getPixel(p1.x, p1.y)) < tolerance_ && !visited[p1.x][p1.y]) {
        pp->add(p1);
    }
    if (p2.y < pp->png_.height() && calculateDelta(*png_.getPixel(curr.x, curr.y), *png_.getPixel(p2.x, p2.y)) < tolerance_ && !visited[p2.x][p2.y]) {
        pp->add(p2);
    }
    if (curr.x && calculateDelta(*png_.getPixel(curr.x, curr.y), *png_.getPixel(p3.x, p3.y)) < tolerance_ && !visited[p3.x][p3.y]) {
        pp->add(p3);
    }
    if (curr.y && calculateDelta(*png_.getPixel(curr.x, curr.y), *png_.getPixel(p4.x, p4.y)) < tolerance_ && !visited[p4.x][p4.y]) {
        pp->add(p4);
    }
    while(!pp->empty()&&pp->visited[pp->peek().x][pp->peek().y]==true){
        pp->pop();
    }
    if(!pp->empty()){
        curr=pp->peek();
    }else{
        curr=Point(-1,-1);
    }
    return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  
  return !(curr==other.curr);
}
