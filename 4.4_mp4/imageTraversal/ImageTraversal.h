#ifndef IMAGETRAVERSAL_H
#define IMAGETRAVERSAL_H

#include <iterator>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();
    Iterator(const Point& temp,ImageTraversal* p):curr(temp),pp(p){}
    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);
  
  private:
    Point curr;
    ImageTraversal* pp;
  };  
    ImageTraversal(const PNG & png, const Point & start, double tolerance):png_(png),start_(start),tolerance_(tolerance){
        visited=new bool*[png_.width()];
        for(unsigned i=0;i<png_.width();i++){
        visited[i]=new bool[png_.height()];
            for(unsigned j=0;j<png_.height();j++){
                visited[i][j]=false;
            }
        }
    }

  virtual Iterator begin() = 0;
  virtual Iterator end() = 0;

  virtual void add(const Point & t) = 0;
  virtual Point pop() = 0;
  virtual Point peek() const = 0;
  virtual bool empty() const = 0;
protected:
    PNG png_;
    Point start_;
    double tolerance_;
    bool **visited;
private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  
};




#endif
