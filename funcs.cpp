#include "funcs.h"
#include <iostream>
#include <fstream>
#include <vector>



// Sample function

// std::string greet(std::string name){
//   return "Hello "+name+"!";
// }
using namespace std;
// Provided functions
// Reads a PGM file.
// Notice that: height and width are passed by reference!
void readImage(std::string filename, int image[MAX_H][MAX_W], int &height, int &width) {
  char c;
  int x;
  std::ifstream instr;
  instr.open(filename.c_str());

  // read the header P2
  instr >> c;
  assert(c == 'P');
  instr >> c;
  assert(c == '2');


  // skip the comments (if any)
  while ((instr>>std::ws).peek() == '#') {
    instr.ignore(4096, '\n');
  }

  instr >> width;
  instr >> height;

  assert(width <= MAX_W);
  assert(height <= MAX_H);
  int max;
  instr >> max;
  assert(max == 255);

  for (int row = 0; row < height; row++)
    for (int col = 0; col < width; col++)
      instr >> image[row][col];
  instr.close();
  return;
}


// Writes a PGM file
// Need to provide the array data and the image dimensions
void writeImage(std::string filename,int image[MAX_H][MAX_W], int height, int width) {
  std::ofstream ostr;
  ostr.open(filename.c_str());
  if (ostr.fail()) {
    std::cout << "Unable to write file\n";
    exit(1);
  };

  // print the header
  ostr << "P2" << std::endl;
  // width, height
  ostr << width << ' ';
  ostr << height << std::endl;
  ostr << 255 << std::endl;


  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      assert(image[row][col] < 256);
      assert(image[row][col] >= 0);
      ostr << image[row][col] << ' ';
      ostr << std::endl;
    }
  }
  ostr.close();
  return;
}
void invert(){
  int img[MAX_H][MAX_W];
  int h,w;
  int inverted_img[MAX_H][MAX_W];
  readImage("test_image.pgm",img, h, w);
  for (size_t row = 0; row < h; row++) {
    for (size_t col = 0; col < w; col++) {
      inverted_img[row][col] = 255 - img[row][col];
    }
  }
  writeImage("taska.pgm", inverted_img, h, w);
}
void invert_half(){
  int img[MAX_H][MAX_W];
  int h,w;
  int inverted_img[MAX_H][MAX_W];
  readImage("test_image.pgm",img, h, w);
  for (size_t row = 0; row < h; row++) {
    for (size_t i = 0; i < w/2; i++) {
      inverted_img[row][i] = img[row][i];
    }
    for (size_t col = w/2; col < w; col++) {
      inverted_img[row][col] = 255 - img[row][col];
    }
  }
  writeImage("taskb.pgm", inverted_img, h, w);
  }

void box(){
  int img[MAX_H][MAX_W];
  int h,w;
  int inverted_img[MAX_H][MAX_W];
  readImage("test_image.pgm",img, h, w);
  for (size_t row = 0; row < h/4; row++) { //the top 1/4 of the image is the same
    for (size_t col = 0; col < w; col++) {
      inverted_img[row][col] = img[row][col];
    }
  }
  for (size_t row = h/4; row < 3*h/4; row++) {
    for (size_t col = 0; col < w/4; col++) {
      inverted_img[row][col] = img[row][col];
    }
    for (size_t col = w/4; col < 3*w/4; col++) {
      inverted_img[row][col] = 255;
    }
    for (size_t col = 3*w/4; col < w; col++) {
      inverted_img[row][col] = img[row][col];
    }
  }
  for (size_t row = 3*h/4; row < h; row++) {
    for (size_t col = 0; col < w; col++) {
      inverted_img[row][col] = img[row][col];
    }
  }
  writeImage("taskc.pgm", inverted_img, h, w);

}
void frame(){
  int img[MAX_H][MAX_W];
  int h,w;
  int inverted_img[MAX_H][MAX_W];
  readImage("test_image.pgm",img, h, w);
  for (size_t row = 0; row < h; row++) {
    for (size_t col = 0; col < w; col++) {
      inverted_img[row][col] = img[row][col];
    }
  }
  for (size_t col = w/4; col<3*w/4; col++) { //top
    inverted_img[h/4][col] = 255;
    inverted_img[3*h/4][col] = 255;
  }
  for (size_t row = h/4; row<3*h/4; row++) { //left fram
    inverted_img[row][w/4] = 255;
    inverted_img[row][3*w/4] = 255;
  }

  writeImage("taskd.pgm", inverted_img, h, w);
}
void scale(){
  int img[MAX_H][MAX_W];
  int h,w;
  int inverted_img[MAX_H][MAX_W];
  readImage("test_image.pgm",img, h, w);
  int h2 = 2*h;
  int w2= 2*w;
  for (size_t row = 0; row <h2-1; row++) {
    for (size_t col = 0; col < w2-1; col++) {
      inverted_img[row][col] = img[row/2][col/2];
      //inverted_img[row+1][col+1] = img[row/2][col/2];
      // if ( col % 2 == 1){
      //     inverted_img[row][col] = img[row][col-1];
      // }
      // // else if (row %2 == 1){
      // //   inverted_img[row][col] = img[row-1][col];
      // // }
      // else{
      //   inverted_img[row][col] = img[row][col];
      // }
    }
  }
  writeImage("taske.pgm", inverted_img, h2, w2);


}
void pixelate(){
  int img[MAX_H][MAX_W];
  int h,w,avg;
  int inverted_img[MAX_H][MAX_W];
  readImage("test_image.pgm",img, h, w);
  for (size_t row = 0; row <h; row+=2) {
    for (size_t col = 0; col < w; col+=2) {
      avg = (img[row][col] + img[row][col+1] + img[row+1][col] +img[row+1][col+1])/4;
      inverted_img[row][col] = avg;
      inverted_img[row][col+1] = avg;
      inverted_img[row+1][col] = avg;
      inverted_img[row+1][col+1] = avg;
    }
  }
  writeImage("taskf.pgm", inverted_img, h, w);
}








































//Garbage:

// int invert(int color){ //this func shud recieves just one color value //not sure if it was best to split this
// return (255-color);
// }
//this is the only one that works
// int invert_general(int img[MAX_H][MAX_W], int height, int width, int starting_row, int starting_col, int ending_row, int ending_col){ //refactoring function
//   int inverted_img[height][width] = {0};
//   int new_color;
//   int rr;
//   int cc;
//   for (int row=starting_row; row < ending_row; row++) {
//     for (int col= starting_col; col < ending_col; col++) {
//       new_color = (255-img[row][col]);
//       inverted_img[row][col] = new_color;
//       rr == row;
//       cc ==col;
//     }
//   }
//   // inverted_img = outImage.pgm;
//   //readImage("test_image.pgm",inverted_img, &inverted_img);
// }
// int invert(int img[MAX_H][MAX_W], int height, int width){
//   int inverted_img[height][width] = {0};
//   inverted_img = invert_general(img[MAX_H][MAX_W],height,width, 0,0,height,width);
//   outImage.pgm = writeImage("test_out.pgm",inverted_img, h, w)
// }
// int invert_half(int img, int height, int width){
//   int inverted_img[height][width];
//   inverted_img = invert_general(img,height,width,0,width/2,height,width);
//   return inverted_img;
// }
// int white_box(int img, int height, int width){
//   int box_img[height][width];
//   int starting_row = height/4;
//   int starting_col = width/4;
//   int ending_row = (3/4)*height;
//   int ending_col = (3/4)*width;
//   box_img = invert_general(img,height,width,starting_row,starting_col,ending_row,ending_col);
//   return box_img;
// }
// int frame(int img,int height,int width){
//   //maybe instead of redoing it each time, i should have variables for the coordinates of the four points of the square
//   int framed[height][width];
//   int starting_row = height/4;
//   int starting_col = width/4;
//   int ending_row = starting_row;
//   int ending_col = (3/4)*width;
//   framed = invert_general(img,height,width,starting_row,starting_col,ending_row,ending_col);//does the top horizontal line
//   ending_row = (3/4)*height; //bottom part of the square
//   ending_col = starting_col;
//   framed = invert_general(framed,height,width,starting_row,starting_col,ending_row,ending_col);//does the lefthand vertical line
//   starting_row = ending_row;
//   ending_col = (3/4)*width;
//   framed = invert_general(framed,height,width,starting_row,starting_col,ending_row,ending_col); //bottom line
//   starting_row = height/4;
//   starting_col=width*(3/4);
//   framed = invert_general(framed,height,width,starting_row,starting_col,ending_row,ending_col);
//
// }
//


// Write all your functions in here
