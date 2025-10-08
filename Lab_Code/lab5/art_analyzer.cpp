#include "pixel_art.h"

// TODO 4: Count Pixels
// Count the number of pixels of a specific type in the canvas
//
// Input:
//  - canvas: 2D array representing the pixel art canvas
//  - targetChar: Character to count
//
// Output:
//  - int: Number of pixels matching targetChar
// Note: Use the global constants CANVAS_HEIGHT and CANVAS_WIDTH for the dimensions
int countPixels(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH], char targetChar) {
    // ** Your TODO: Implement this function. **
    int count = 0;
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        for (int j = 0; j < CANVAS_WIDTH; j++)
        {
            if(canvas[i][j] == targetChar){
                count++;
            }
        }
        
    }
    return count;
    
}
