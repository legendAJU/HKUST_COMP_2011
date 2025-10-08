#include "pixel_art.h"

// TODO 1: Clear Canvas
// Clear the entire canvas by filling it with background pixels
//
// Input:
//  - canvas: 2D array representing the pixel art canvas
//
// Function: Set every pixel in the canvas to '.' (dot character for empty space)
// Note: Use the global constants CANVAS_HEIGHT and CANVAS_WIDTH for the dimensions
void clearCanvas(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH]) {
    // ** Your TODO: Implement this function. **
    for (int i = 0; i < CANVAS_HEIGHT; i++)
    {
        for (int j = 0; j < CANVAS_WIDTH; j++)
        {
            canvas[i][j] = '.';
        }
        
    }
    
    
}

