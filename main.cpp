#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "funcs.h"


int main()
{

  // sample code

  invert();
  invert_half();
  box();
  frame();
  scale();
  pixelate();
  int img[MAX_H][MAX_W];
  int h, w;
  readImage("test_image.pgm",img, h, w); // read it from the file "inImage.pgm"

  // h and w were passed by reference and
  // now contain the dimensions of the picture
  // and the 2-dimesional array img contains the image data

  // Now we can manipulate the image the way we like
  // for example we copy its contents into a new array
  int out[MAX_H][MAX_W];

  for(int row = 0; row < h; row++) {
    for(int col = 0; col < w; col++) {
      out[row][col] = img[row][col];
    }
  }

  // and save this new image to file "outImage.pgm"
  writeImage("test_out.pgm",out, h, w);


return 0;
}
