#pragma once

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

// sample signature
std::string greet(std::string name);

// provided stuff
#define MAX_H 512
#define MAX_W 512

void readImage(std::string filename, int image[MAX_H][MAX_W], int &height, int &width);
void writeImage(std::string filename,int image[MAX_H][MAX_W], int height, int width);

// Write your function signatures / prototypes here
