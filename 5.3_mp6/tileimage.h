/**
 * tileimage.h (v2)
 * Definition of the TileImage class.
 */

#ifndef TILEIMAGE_H
#define TILEIMAGE_H

#include <math.h>
#include <stdint.h>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

/**
 * Represents a Tile in the Photomosaic.
 */
class TileImage {
  private:
    PNG image_;
    HSLAPixel averageColor_;
    int pixels;
  public:
    TileImage();
    explicit TileImage(const PNG& source,int pixelsPerTile=0);//

    HSLAPixel getAverageColor() const { return averageColor_; }
    //int getResolution() const { return image_.width(); }
    void paste(PNG& canvas, int startX, int startY, int resolution);

  private:
  
    static PNG generateResizedImage(int resolution,const PNG &cropped);     // 
    static PNG cropSourceImage(const PNG& source,int pixelsPerTile=0);//
    static HSLAPixel calculateAverageColor(const PNG& image_);
    static HSLAPixel getScaledPixelDouble(double startX, double endX,
                                   double startY, double endY,const PNG &cropped);
    static HSLAPixel getScaledPixelInt(int startX, int endX,
                                int startY, int endY,const PNG &cropped);
    static uint64_t divide(uint64_t a, uint64_t b) {
      return (a + b / 2) / b;
    }
    static int divide(int a, int b) {
        return divide(static_cast<uint64_t>(a), static_cast<uint64_t>(b));
    }
    static int fdivide(double a, double b) {
        return a / b + 0.5;
    }
    static double frac(double x) {
        return x - floor(x);
    }
};

#endif // TILEIMAGE_H
