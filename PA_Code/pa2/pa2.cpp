#include <iostream>
#include <fstream>
using namespace std;
const int N = 19;
const char EMPTY = '.';
const char BLACK = '@';
const char WHITE = 'o';


/*helper function: check row, col are in board*/
bool inBoardBound(int row, int col, int boardSize)
{
    return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
}
/*helper function: check the color is defined*/
bool definedColor(int color)
{
    return color == BLACK || color == WHITE;
}


/*helper function: display a board*/
void display_board(int boardSize, const char board[][N])
{
    // Print column indices
    cout << "  ";
    for (int col = 0; col < boardSize; col++) {
        cout << col << ' ';
    }
    cout << endl;
    
    // Print top boundary
    cout << " +";
    for (int col = 0; col < boardSize; col++) {
        cout << "-+";
    }
    cout << endl;
    
    // Print rows with left and right boundaries
    for (int row = 0; row < boardSize; row++) {
        cout << row << "|"; // Row index and left boundary
        
        // Print board content
        for (int col = 0; col < boardSize; col++) {
            // Display white space if entry is '.', otherwise show character
            if(board[row][col] == EMPTY) cout << ' ';
            else if(board[row][col] == BLACK) cout << "\u25CB"; // for displaying white stones
            else cout << "\u25CF"; // for displaying black stones
            cout <<"|";
            // cout << (board[row][col] == empty ? ' ' : board[row][col]) << "|";
        }
        cout << endl;
        
        // Print horizontal boundary after each row
        cout << " +";
        for (int col = 0; col < boardSize; col++) {
            cout << "-+";
        }
        cout << endl;
    }
}
/*helper function: copy board to tempBoard*/
void copyBoard(int boardSize, const char board[][N], char tempBoard[][N])
{
    for(int i = 0; i < boardSize; ++i) 
        for(int j = 0; j < boardSize; ++j)
            tempBoard[i][j] = board[i][j];
}
/*helper function: checking whether the two boards are the same*/
bool sameBoard(int boardSize, const char board1[][N], const char board2[][N])
{
    
    for(int i = 0; i < boardSize; ++i) for(int j = 0; j < boardSize; ++j)
        if(board1[i][j] != board2[i][j]) return false;
    return true;
}


//=== Start of PA2 tasks
/**
 * @brief Counts the number of liberties (empty adjacent spaces) for a stone group of the specified color.
 * 
 * This function recursively traverses the connected group of stones with the specified color starting
 * from the given position (row, col) and counts how many liberties (empty adjacent intersections) this
 * group has. The function uses a visit array to ensure no position is counted twice.
 * 
 * @param boardSize The size of the Go board
 * @param board The 2D array representing the current state of the Go board
 * @param row The row position of the current stone
 * @param col The column position of the current stone
 * @param color The color of the stone group to check ('@' for black or 'o' for white)
 * @param visit A 2D boolean array to mark visited positions to avoid double counting
 * @param cnt Reference to an integer that accumulates the liberty count for the stone group
 * 
 * @note This function assumes it is only called for positions that contain a stone (non-empty).
 * @note A liberty is an empty cell adjacent to a stone.
 * @note This function can be used to determine if a stone group is captured (when liberty count is 0).
 * @note This function must be implemented recursively as per requirements.
 */
void countLiberty(int boardSize,const char board[][N], int row, int col, const char color, bool visit[][N], int& cnt) 
{
    // TODO: Task 1.1
    // 1. Base case
    //  (1) out of. boundary
    

    //  (2) already visit
    
   
    //  (3) this group is not dead
    

    //  (4) touch another color

    
    
    // 2. Recursive case
    
}

/**
 * @brief Checks if a stone group is captured (dead) according to Go rules.
 * 
 * In Go, a stone group is captured when it has no liberties (empty adjacent intersections).
 * This function checks if the stone group containing the piece at (row, col) is captured.
 * 
 * @param boardSize The size of the Go board
 * @param board The 2D array representing the current state of the Go board
 * @param row The row position of the current stone
 * @param col The column position of the current stone
 * @param color The color of the stone group to check ('@' for black or 'o' for white)
 * @param visit A 2D boolean array to track visited positions during the liberty counting process.
 * @return true if the stone group is captured (has no liberties), false otherwise.
 * 
 * @note This function assumes it is only called for positions that contain a stone (non-empty).
 */
bool isCaptured(int boardSize, const char board[][N] , int row, int col,  char color, bool visit[][N]) 
{
    // TODO: Task 1.2
    // check whether the group of (row, col) is dead w.r.t color
    

}


/**
 * @brief Recursively removes a group of stones of the given `color` without checking whether it's captured or not, starting from the cell at (row, col).
 * 
 * This function removes a connected group of stones of the specified color. The function traverses the 
 * group recursively from the starting position and removes all connected stones of the same color.
 * 
 * @param boardSize The size of the Go board
 * @param board The 2D array representing the current state of the Go board
 * @param row The row position of the current stone
 * @param col The column position of the current stone
 * @param color The color of the stone group to check ('@' for black or 'o' for white)
 * 
 * @return The number of stones removed from the board
 * 
 * @note This function must be implemented recursively as per requirements.
 */
int removeStones(int boardSize, char board[][N], int row, int col, const char color) 
{
    // TODO: Task 2.1
    // remove the group of `color` starting from (row, col) , return the size of this removed group
    

}


/**
 * @brief Updates the board state after placing a stone of the given color at (row, col).
 *
 * This function checks each adjacent group of the opponent's color and removes any that 
 * become captured (i.e., have zero liberties). Returns the total number of stones removed.
 *
 * @param boardSize The size of the Go board
 * @param board The 2D array representing the current state of the Go board
 * @param row The row position of the current stone
 * @param col The column position of the current stone
 * @param color The color of the stone group to check ('@' for black or 'o' for white). 
 * @return The total number of opponent stones removed after this move
 *
 * @note This function assumes that placing the stone at (row, col) is a legal move.
 */
int updateBoard(int boardSize, char board[][N], int row, int col, char color)
{
    // TODO: Task 2.2
    // we assume the stone we just put in (row, col) is legal
    // we update the board after putting a stone at (row, col) , returne how many stones is captured by this move
    

}

/**
 * @brief Determines if placing a stone at a specific position is a legal move in Go.
 * 
 * This function checks whether a player can legally place a stone at the specified position 
 * on the board according to Go rules. It evaluates three conditions:
 * 1. The target cell must be empty
 * 2. The move must not be doomed (capturing one's own stones)
 * 3. The move must not violate the Ko rule (recreating a previous board state)
 * 
 * @param boardSize The size of the Go board
 * @param board The 2D array representing the current state of the Go board
 * @param row The row position of the current stone
 * @param col The column position of the current stone
 * @param color The color of the stone group to check ('@' for black or 'o' for white)
 * @param previousBoard The board state after this player's previous move (before opponent's last move)
 * @return true if the move is legal, false otherwise
 * 
 * @note The function first checks if the position is within board boundaries and if
 *       the target cell is empty before proceeding to more complex rule validations.
 */
bool isLegalMove(int boardSize, const char board[][N], int row, int col, char color, const char previousBoard[][N]) 
{

    // TODO: Task 3.1
    // determine whether a player can put stone at the entry (You don't have to follow rules order listed below since they are just listed out for remider)

    // 0. In Range: Not outside of the boundary
    // 1. Empty: can put stone only if the cell is empty
    // 2. Liberty > 0 (Doom Prohibition)
    // 3. Repetition Prohibition: The updated board after putting the stone is not the same as previousBoard (you may use some given helper function) 


}

//=== End of PA2 tasks === 

/*helper function: for playing a legal move*/
bool playMove(int boardSize, char board[N][N], int row, int col, char color, char previousBoardBlack[N][N], char previousBoardWhite[N][N])
{
    // play the move if it's legal
    if(color == BLACK && isLegalMove(boardSize, board, row, col, color, previousBoardBlack))
    {
        board[row][col] = color;
        updateBoard(boardSize, board, row, col, color);
        copyBoard(boardSize, board, previousBoardBlack);  // update the board that played after black
        return true;  
    }

    else if(color == WHITE && isLegalMove(boardSize, board, row, col, color, previousBoardWhite))
    {
        board[row][col] = color;
        updateBoard(boardSize, board, row, col, color);
        copyBoard(boardSize, board, previousBoardWhite); // update the board after white 
        return true;
    }
    return false;
}


/*helper function: for loading a board*/
void loadBoard(int& boardSize, char board[N][N])
{
    char filename[100];
    cout << "Enter the file map name:\n";
    cin >> filename;
    
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: Cannot open " << filename << endl;
        return;
    }

    fin >> boardSize;

    // Read the board configuration
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            fin >> board[i][j];
        }
    }

    fin.close();
}


/*helper function header: for interative playing Go*/
void interactiveMode();

/*helper function header: for testing testcases*/
void testingTestcases();





int main()
{
    

    // // /* for testing testcases */
    testingTestcases();

    // /* for interative mode*/
    // interativeMode();

    return 0;
}

enum TestCase {
    PUT_STONE = 1,
    TEST_COUNT_LIBERTY,
    TEST_IS_CAPTURED,
    TEST_REMOVE_STONES,
    TEST_UPDATE_BOARD,
    TEST_IS_LEGAL_MOVE,
    PLAY_MOVE,
    QUIT
};

void interactiveMode()
{
    int boardSize = 19;
    static char board[N][N] = {};
    // Previous board afrer black move
    static char previousBoardBlack[N][N] = {};
    // Previous board afrer white move
    static char previousBoardWhite[N][N] = {};
    
    
    // Display the initial board
    display_board(boardSize, board);

    char color = BLACK;
    while(true)
    {
        // Get a move from black
        color = BLACK;
        cout <<"Black turn: where do you want to put?\n";
        display_board(boardSize, board);
        int row, col;
        cin>>row>>col;
        // Iterate until getting a valid move from black
        while(!playMove(boardSize, board, row, col, color, previousBoardBlack, previousBoardWhite))
        {
            cout <<"Your choice is illegal, please choose another position\n";
            display_board(boardSize, board);
            cin>>row>>col;
        }
        cout <<"White turn: where do you want to put?\n";
        display_board(boardSize, board);
        cin>>row >>col;
        color = WHITE;
        // Iterate until getting a valid move from white
        while(!playMove(boardSize, board, row, col, color, previousBoardBlack, previousBoardWhite))
        {
            cout <<"Your choice is illegal, please choose another position\n";
            display_board(boardSize, board);
            cin>>row>>col;
        }

    }
}


void testingTestcases()
{
    int boardSize = 0;
    static char board[N][N] = {};
    // Previous board afrer black move
    static char previousBoardBlack[N][N] = {};
    // Previous board afrer white move
    static char previousBoardWhite[N][N] = {};
    
   

    // load board
    loadBoard(boardSize, board);
    
    // Copy the initial board to the previous boards
    copyBoard(boardSize, board, previousBoardBlack);
    copyBoard(boardSize, board, previousBoardWhite);
    
    // Display the initial board
    display_board(boardSize, board);
    
    // Display available test case options
    cout << "Available operations:" << endl;
    cout << "1: PUT_STONE - Place a stone on the board (input: row col color)" << endl;
    cout << "2: TEST_COUNT_LIBERTY - Count liberties of a stone group (input: row col)" << endl;
    cout << "3: TEST_IS_CAPTURED - Check if a stone group is captured (input: row col)" << endl;
    cout << "4: TEST_REMOVE_STONES - Remove a stone group (input: row col)" << endl;
    cout << "5: TEST_UPDATE_BOARD - Update board after placing a stone (input: row col color)" << endl;
    cout << "6: TEST_IS_LEGAL_MOVE - Check if a move is legal (input: row col color)" << endl;
    cout << "7: PLAY_MOVE - Make a move in the game (input: row col color)" << endl;
    cout << "8: Quit the program" << endl;
    cout << endl;


    // Process queries
    int testCase;

    while (cin >> testCase) {
        cout << "Which operation you would like to perform? (entering a number)" << endl;
        switch (testCase)
        {
        case PUT_STONE:
            {
                int row, col; char color;
                cout << "Enter the row, column, and color (o for white, @ for black) separated by spaces: \n";
                cin >> row >> col >> color;
                if (inBoardBound(row, col, boardSize) && definedColor(color) && board[row][col] == EMPTY) {
                    board[row][col] = color;
                    cout << "Put " << color << " at (" << row << ", " << col << ")" << endl;
                    display_board(boardSize, board);
                } else {
                    cout << "Invalid input! The position should be in board range and empty, and the color should be either @ or o" << endl;
                    break;
                }
            }
            break;
            
        case TEST_COUNT_LIBERTY:
            {
                int row, col;
                cout << "Enter the row, and column separated by spaces: \n";
                cin >> row >> col;
                if(!inBoardBound(row, col, boardSize))
                {
                    cout << "Invalid input! The position should be in board range." <<endl;
                    break;
                }
                if(board[row][col] == EMPTY) 
                {
                    cout << "The cell is empty, which makes no sense to count liberty. \n";
                    break;
                }
                bool visit[N][N] = {};
                int count = 0;
                countLiberty(boardSize, board, row, col, board[row][col], visit, count);
                cout << "Liberty count at (" << row << ", " << col << "): " << count << endl;
            }
            break;
        
        case TEST_IS_CAPTURED:
            {
                int row, col;
                cout << "Enter the row, and column separated by spaces: \n";
                cin >> row >> col;
                bool visit[N][N] = {};
                if(!inBoardBound(row, col, boardSize))
                {
                    cout << "Invalid input! The position should be in board range." <<endl;
                    break;
                }
                if(board[row][col]==EMPTY)
                {
                    cout <<"Invalid input! The cell is empty, which makes no sense to determine whether it's captured or not.\n";
                    break;
                }
                bool captured = isCaptured(boardSize, board, row, col, board[row][col], visit);
                cout << "(" << row << ", " << col << ") Is captured: " << (captured ? "Yes" : "No") << endl;
            }
            break;
        
        case TEST_REMOVE_STONES:
            {
                int row, col;
                cout << "Enter the row, and column separated by spaces: \n";
                cin >> row >> col;
                if(!inBoardBound(row, col, boardSize))
                {
                    cout << "Invalid input! The position should be in board range." <<endl;
                    break;
                }
                if(board[row][col] == EMPTY) 
                {
                    cout << "Invalid input! The cell is empty, which makes no sense to remove.\n";
                    break;
                }
                int removed = removeStones(boardSize, board, row, col, board[row][col]);
                cout << "Removing from (" << row << ", " << col << ") causes " << removed << " stones removed" << endl;
                display_board(boardSize, board);
            }
            break;
        
        case TEST_UPDATE_BOARD:
            {
                int row, col;
                char color;
                cout << "Enter the row, column, and color (o for white, @ for black) separated by spaces: \n";
                cin >> row >> col >> color;
                if(!(inBoardBound(row, col, boardSize)&& definedColor(color)))
                {
                    cout << "Invalid input! The position should be in board range and the color should be either @ or o" <<endl;
                    break;
                }
               
                int removed = updateBoard(boardSize, board, row, col, color);
                cout << "Putting " << color << " at (" << row << ", " << col << ") causes " << removed << " stones captured" << endl;
                display_board(boardSize, board);
            }
            break;
            
        case TEST_IS_LEGAL_MOVE:
            {
                int row, col;
                char color;
                cout << "Enter the row, column, and color (o for white, @ for black) separated by spaces: \n";
                cin >> row >> col >> color;
                // we don't need since we assume the student have handle this
                // if(!(inBoardBound(row, col, boardSize)&& definedColor(color)))
                // {
                //     cout << "Invalid input! The position should be in board range and the color should be either @ or o" <<endl;
                //     break;
                // }
                bool legal = isLegalMove(boardSize, board, row, col, color, 
                                        (color == BLACK) ? previousBoardBlack : previousBoardWhite);
                cout << "(" << row << ", " << col << ", " << color << ") is legal move: " << (legal ? "Yes" : "No") << endl;
            }
            break;
        
        case PLAY_MOVE:
            {
                int row, col;
                char color;
               cout << "Enter the row, column, and color (o for white, @ for black) separated by spaces: \n";
                cin >> row >> col >> color;
                // we assume the student has handle this
                //  if(!(inBoardBound(row, col, boardSize)&& definedColor(color)))
                // {
                //     cout << "Invalid input! The position should be in board range and the color should be either @ or o" <<endl;
                //     break;
                // }
                bool played = playMove(boardSize, board, row, col, color, previousBoardBlack, previousBoardWhite);
                cout << "Playing (" << row << ", " << col << ", " << color << ") is " << (played ? "successful" : "failed") << endl;
                display_board(boardSize, board);
            }
            break;
        case QUIT:
        {
            cout << "End of the program." <<endl;
            return;
        }
        default:
            cout << "Invalid test case!" << endl;
            break;
        }
    }
    
}




