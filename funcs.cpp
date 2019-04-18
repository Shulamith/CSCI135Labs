#include "funcs.h"
#include <iostream>



// Sample function

// std::string greet(std::string name){
//   return "Hello "+name+"!";
// }
//using namespace std;
// Provided functions
// Reads a PGM file.
// Notice that: height and width are passed by reference!
void readImage(std::string filename, int image[MAX_H][MAX_W], int &height, int &width) {
  char c;
  int x;
  ifstream instr;
  instr.open(filename);

  // read the header P2
  instr >> c;
  assert(c == 'P');
  instr >> c;
  assert(c == '2');

  // skip the comments (if any)
  while ((instr>>ws).peek() == '#') {
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
  ofstream ostr;
  ostr.open(filename);
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

// int invert(int color){ //this func shud recieves just one color value //not sure if it was best to split this
// return (255-color);
// }
int invert_general(int img, int starting_row, int starting_col, int ending_row, int ending_col){ //refactoring function
  int inverted_img[height][width];
  for (int row=starting_row; i < ending_row; row++) {
    for (int col= starting_col; i < ending; col++) {
      inverted_img[row][col] = 255-(img[row][col]);
    }
  }
  return inverted_img;
}
int invert(int img, int height, int width){
  int inverted_img[height][width];
  inverted_img = invert_general(img, 0,0,height,width);
  return inverted_img;
}
int invert_half(int img, int height, int width){
  int inverted_img[height][width];
  inverted_img = invert_general(img,0,width/2,height,width);
  return inverted_img;
}
int white_box(int img, int height, int width){
  int box_img[height][width];
  int starting_row = height/4;
  int starting_col = width/4;
  int ending_row = (3/4)*height;
  int ending_col = (3/4)*
  box_img = invert_general(img,starting_row,starting_col,ending_row,ending_col);
  return box_img;
}
int frame(int img,int height,int width){
  int framed[height][width];s
}



// Write all your functions in here
