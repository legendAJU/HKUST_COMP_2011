#include <iostream>
#include <fstream>
using namespace std;

const int MAX_PATH_LENGTH = 100; // maximum length of a file path
const int NUM_LEVELS = 5; // total number of levels

int apply_operation(int current_count, char operation, int operand) {
    // TODO: implement this function
    // Apply the specified mathematical operation to current_count using operand
    // Supported operations: '+', '-', '*', '/'
    // If an operation is not supported, simply return current_count
    // Otherwise, return the result of the operation
    // Note: Assume division by zero won't occur in the input
    //       Assume no negative numbers will be involved
    if (operation == '+'){
        current_count += operand;
    }
    else if (operation == '-'){
        current_count -= operand;
    }
    else if (operation == '*'){
        current_count *= operand;
    }
    else if (operation == '/'){
        current_count /= operand;
    }
    return current_count;
    

    // End of TODO
}

void choose_gate(int& current_count, bool chosen_gate, char operation0, int operand0, char operation1, int operand1) {
    // TODO: Implement this function using apply_operation
    // Choose between two gates and update the count based on the gate selection
    //     If chosen_gate is 0: update current_count using operation0 and operand0
    //     If chosen_gate is 1: update current_count using operation1 and operand1
    if (chosen_gate){
        current_count = apply_operation(current_count,operation1,operand1);
    }
    else{
        current_count = apply_operation(current_count,operation0,operand0);
    }
    

    // End of TODO
}

bool choose_gate_by_dumb_bot(int& current_count, char operation0, int operand0, char operation1, int operand1) {
    // TODO: Implement this function using choose_gate
    // Simulate a dumb bot that automatically chooses a gate based on these rules:
    // 1. Compare the two operations first (preference order: '*' > '+' > '-' > '/')
    //    Hint: Remember that char type variables in C++ are numbers in nature, and the chars in the preference order are in increasing order
    // 2. If operations are identical, choose the gate with the higher operand
    // Update current_count and return the chosen gate accordingly
    // Note: Assume that the operations and operands will not be identical at the same time
    if(operation0 < operation1){
        choose_gate(current_count,false,operation0,operand0,operation1,operand1);
        return false;
    }
    else if(operation0 > operation1){
        choose_gate(current_count,true,operation0,operand0,operation1,operand1);
        return true;
    }
    else{
        if(operand0 > operand1){
            choose_gate(current_count,false,operation0,operand0,operation1,operand1);
            return false;
        }
        else{
            choose_gate(current_count,true,operation0,operand0,operation1,operand1);
            return true;
        }
    }
    

    // End of TODO
}

int main() {

    cout << "Welcome to Lab3: Count Masters!" << endl;

    // Read the input file path
    char file_path[MAX_PATH_LENGTH];
    cout << "Enter the input file name: ";
    cin >> file_path;
    ifstream fin(file_path);

    // Check if the file can be opened
    if (!fin) {
        cout << "Error: Can not open " << file_path << endl; 
        return -1;
    }

    int current_count = 0, prev_count;
    bool victory = true, chosen_gate;

    // Parameters to be read in the input file
    char operation0, operation1;
    int operand0, operand1, target_count;

    for (int i = 0; i < NUM_LEVELS; i++) {

        // TODO: fill this part
        // Read level data from the input file
        // Format: operation0 operand0 operation1 operand1 target_count
        // Example: + 5 * 2 15
        // Hint: You only need to use the >> operator to read from the file
        // Notice: There's another TODO below to close the file after the loop
        fin >> operation0;
        fin >> operand0;
        fin >> operation1;
        fin >> operand1;
        fin >> target_count;
        // End of TODO
        
        cout << "--------------------" << endl;
        cout << "Level " << i << endl;
        cout << "Gate 0: " << operation0 << " " << operand0 << endl;
        cout << "Gate 1: " << operation1 << " " << operand1 << endl;
        cout << "Target: " << target_count << endl;

        prev_count = current_count;
        chosen_gate = choose_gate_by_dumb_bot(current_count, operation0, operand0, operation1, operand1);

        cout << "Chosen Gate: " << chosen_gate << endl;
        cout << "Count Update: " << prev_count << " -> " << current_count << endl;

        if (current_count < target_count) {
            cout << "--------------------" << endl;
            cout << "Game over! TAT" << endl;
            victory = false;
            break;
        }
    }

    if (victory) {
        cout << "--------------------" << endl;
        cout << "Victory! ^v^" << endl;
    }

    // TODO: fill this part
    // Close the file
    fin.close();
    
    
    // End of TODO

    return 0;
}