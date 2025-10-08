#include "pixel_art.h"
#include <unistd.h>

// Global variable definition
bool isOutputRedirected;

// Utility function to print the canvas
void printCanvas(char canvas[CANVAS_HEIGHT][CANVAS_WIDTH]) {
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            cout << canvas[i][j];
        }
        cout << endl;
    }
}

int main() {
    // Check if output is redirected to a file
    isOutputRedirected = !isatty(STDOUT_FILENO);
    
    // Display welcome message only when not redirected
    if (!isOutputRedirected) {
        cout << "Welcome to Pixel Art Studio!" << endl << endl;
    }
    
    // Output canvas size to file when redirected
    if (isOutputRedirected) {
        cout << "Canvas Size " << CANVAS_HEIGHT << "x" << CANVAS_WIDTH << endl;
    }
    
    // Initialize canvas statically
    char mainCanvas[CANVAS_HEIGHT][CANVAS_WIDTH];
    
    // Start with a clear canvas
    clearCanvas(mainCanvas);
    
    char choice;
    do {
        // Show interactive menu only when not redirected
        if (!isOutputRedirected) {
            cout << "Current Canvas:" << endl;
            printCanvas(mainCanvas);
            cout << endl;
            
            cout << "Choose your tool:" << endl;
            cout << "a. Clear Canvas" << endl;
            cout << "b. Draw Border" << endl;
            cout << "c. Fill Rectangle " << endl;
            cout << "d. Count Pixels" << endl;
            cout << "x. Exit Studio" << endl;
            cout << "Enter your choice: ";
        }
        
        cin >> choice;
        
        switch (choice) {
            case 'a': {
                if (!isOutputRedirected) {
                    cout << "Canvas cleared!" << endl << endl;
                } else {
                    cout << "Clear Canvas" << endl;
                }
                clearCanvas(mainCanvas);
                if (isOutputRedirected) {
                    printCanvas(mainCanvas);
                    cout << endl;
                }
                break;
            }
            case 'b': {
                char borderChar;
                if (!isOutputRedirected) {
                    cout << "Enter border character: ";
                }
                cin >> borderChar;
                if (!isOutputRedirected) {
                    cout << "Border drawn with '" << borderChar << "'!" << endl << endl;
                } else {
                    cout << "Draw Border " << borderChar << endl;
                }
                drawBorder(mainCanvas, borderChar);
                if (isOutputRedirected) {
                    printCanvas(mainCanvas);
                    cout << endl;
                }
                break;
            }
            case 'c': {
                int startRow, startCol, height, width;
                char fillChar;
                if (!isOutputRedirected) {
                    cout << "Enter start row: ";
                    cin >> startRow;
                    cout << "Enter start column: ";
                    cin >> startCol;
                    cout << "Enter height: ";
                    cin >> height;
                    cout << "Enter width: ";
                    cin >> width;
                    cout << "Enter fill character: ";
                    cin >> fillChar;
                    cout << "Rectangle filled at (" << startRow << "," << startCol 
                         << ") with size " << height << "x" << width 
                         << " using '" << fillChar << "'!" << endl << endl;
                } else {
                    cin >> startRow >> startCol >> height >> width >> fillChar;
                    cout << "Fill Rectangle " << startRow << " " << startCol << " " << height << " " << width << " " << fillChar << endl;
                }
                fillRectangle(mainCanvas, startRow, startCol, height, width, fillChar);
                if (isOutputRedirected) {
                    printCanvas(mainCanvas);
                    cout << endl;
                }
                break;
            }
            case 'd': {
                char targetChar;
                if (!isOutputRedirected) {
                    cout << "Enter character to count: ";
                }
                cin >> targetChar;
                int count = countPixels(mainCanvas, targetChar);
                if (!isOutputRedirected) {
                    cout << "Found " << count << " pixels of type '" << targetChar << "'" << endl << endl;
                } else {
                    cout << "Count Pixels " << targetChar << " " << count << endl;
                    printCanvas(mainCanvas);
                    cout << endl;
                }
                break;
            }
            case 'x':
                if (!isOutputRedirected) {
                    cout << "Thanks for using Pixel Art Studio! Your creations are saved!" << endl;
                } else {
                    cout << "Exit" << endl;
                }
                break;
            default:
                if (!isOutputRedirected) {
                    cout << "Invalid choice! Please try again." << endl << endl;
                }
                break;
        }
    } while (choice != 'x');
    
    return 0;
}