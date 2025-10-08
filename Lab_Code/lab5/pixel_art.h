#ifndef PIXEL_ART_H
#define PIXEL_ART_H

#include <iostream>
using namespace std;

// Global constants for canvas dimensions
const int CANVAS_HEIGHT = 8;
const int CANVAS_WIDTH = 16;

// Function declarations for canvas_operations.cpp
void clearCanvas(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH]);

// Function declarations for pattern_generator.cpp
void drawBorder(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH], char borderChar);
bool isValidRectangle(int startRow, int startCol, int height, int width);
void fillRectangle(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int startRow, int startCol, 
                int height, int width, char fillChar);

// Function declarations for art_analyzer.cpp
int countPixels(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH], char targetChar);

// Utility functions (implemented in main.cpp)
void printCanvas(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH]);

#endif