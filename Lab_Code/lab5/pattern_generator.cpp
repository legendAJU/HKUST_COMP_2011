#include "pixel_art.h"

// TODO 2: Draw Border
// Draw a decorative border around the canvas edges
//
// Input:
//  - canvas: 2D array representing the pixel art canvas
//  - borderChar: Character to use for the border (e.g., '#')
//
// Function: Draw border on the outermost edge of the canvas
// Note: Use the global constants CANVAS_HEIGHT and CANVAS_WIDTH for the dimensions
void drawBorder(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH], char borderChar) {
    // ** Your TODO: Implement this function. **
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        if(i != 0 && i != CANVAS_HEIGHT - 1){
            canvas[i][0] = borderChar;
            canvas[i][CANVAS_WIDTH-1] = borderChar;
        }
        else{
            for (int j = 0; j < CANVAS_WIDTH; j++)
            {
                canvas[i][j] = borderChar;
            }
            
        }
    }
}

// TODO 3a: Check Rectangle Bounds
// Check if a rectangle is completely within the canvas boundaries
//
// Input:
//  - startRow, startCol: Starting position (top-left corner)
//  - height, width: Dimensions of the rectangle
//
// Function: Return true if the entire rectangle fits within canvas bounds
// Note: Use the global constants CANVAS_HEIGHT and CANVAS_WIDTH for boundary checking
// Note: This prevents array out-of-bounds errors
bool isValidRectangle(int startRow, int startCol, int height, int width) {
    // ** Your TODO: Implement this function. **
    // check boundaries first
    if ( startRow >= 0 && startCol >=0  && startRow + height - 1 < CANVAS_HEIGHT - 1 && startCol + width - 1 < CANVAS_WIDTH - 1){
        return true;
    }
    return false;
}

// TODO 3b: Fill Rectangle
// Fill a rectangular area with a specific pattern character
//
// Input:
//  - canvas: 2D array representing the pixel art canvas
//  - startRow, startCol: Starting position (top-left corner)
//  - height, width: Dimensions of the area to fill
//  - fillChar: Character to use for filling
//
// Function: Fill the specified rectangular area with fillChar
// Note: Check bounds using isValidRectangle() before filling
// Note: Only fill if the rectangle is completely within bounds
void fillRectangle(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int startRow, int startCol, 
                int height, int width, char fillChar) {
    // First check if the rectangle is valid
    if (!isValidRectangle(startRow, startCol, height, width)) {
        cout << "Invalid rectangle bounds, canvas remains unchanged" << endl;
        return; // Do nothing if rectangle is out of bounds
    }
    for (int i = startRow; i < startRow + height; i++)
    {
        for (int j = startCol; j < startCol + width; j++)
        {
            canvas[i][j] = fillChar;
        }
    }
    
    // Fill the rectangular area (we know it's safe now)
    // ** Your TODO: Implement this function. **

}