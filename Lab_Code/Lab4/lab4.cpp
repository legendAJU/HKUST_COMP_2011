#include <iostream>
#include <iomanip>
using namespace std;

// Maximum capacity of the queue system
const int MAX_QUEUE_LENGTH = 5;

/*
 * TASK 1: initialize_queue_system
 *   - Initialize the queue with all 0s
 */
void initialize_queue_system(int queue[])
{
    // TODO: set all entries to 0
    for (int i = 0; i < MAX_QUEUE_LENGTH; i++){
        queue[i] = 0;
    }
}

/*
 * TASK 2: take_a_queue_ticket
 *   - Add next_ticket_number to the first empty slot (0)
 *   - Increment next_ticket_number
 *   - Return true if added successfully, false if the queue is full
 */
bool take_a_queue_ticket(int queue[], int &next_ticket_number)
{
    // TODO
    for (int i = 0; i < MAX_QUEUE_LENGTH; i++)
    {
        if(queue[i]==0){
            queue[i] = next_ticket_number;
            next_ticket_number++;
            return true;
        }
    }
    
    return false;
}

/*
 * TASK 3: serve_the_first_come_customer
 *   - Remove the first ticket (front of the array) if any
 *   - Shift the remaining tickets to the left
 *   - Put 0 at the tail
 *   - Return true if served successfully, false if empty
 */
bool serve_the_first_come_customer(int queue[])
{
    // TODO
    if(queue[0] != 0){
        queue[0] = 0;
        for (int i = 1; i < MAX_QUEUE_LENGTH; i++)
        {
            if(queue[i] != 0){
                queue[i - 1] = queue[i];
                queue[i] = 0;
            }
        }
        return true;
    }
    return false;
}

/*
 * TASK 4: cancel_queue_ticket
 *   - A customer decides to cancel waiting.
 *   - Remove the given ticket_number from the queue if it exists.
 *   - Shift the remaining tickets to the left and put 0 at the tail.
 *   - Return true if found and removed; otherwise false.
 */
bool cancel_queue_ticket(int queue[], int ticket_number)
{
    // TODO
    for (int i = 0; i < MAX_QUEUE_LENGTH; i++)
    {
        if (queue[i] == ticket_number){
            queue[i] = 0;
            for (int j = i+1; j < MAX_QUEUE_LENGTH; j++)
            {
                if(queue[j] != 0){
                    queue[j-1]=queue[j];
                    queue[j] = 0;
                }
            }
            return true;
        }
    }
    
    
    return false;
}

/*
 * TASK 5: check_position
 *   - Ask for a ticket number
 *   - Return its current position in the queue (1 = front)
 *   - If not found, return -1
 */
int check_position(const int queue[], int ticket_number)
{
    for (int i = 0; i < MAX_QUEUE_LENGTH; i++)
    {
        if (queue[i] == ticket_number){
            return i+1;
        }
    }
    
    return -1;
}

// Given: Print the current queue info to terminal
void show_current_queue(const int queue[])
{
    cout << "<-- [ ";
    for (int i = 0; i < MAX_QUEUE_LENGTH; ++i)
    {
        cout << queue[i] << " ";
    }
    cout << "] <--" << endl;

    cout << "========================================" << endl;
    cout << "|          TICKET QUEUE SYSTEM         |" << endl;
    cout << "|======================================|" << endl;
    for (int i = 0; i < MAX_QUEUE_LENGTH; ++i)
    {
        if (queue[i] == 0)
            cout << "|              EMPTY SLOT              |" << endl;
        else
            cout << "|             Ticket #" << setw(4) << queue[i] << "             |" << endl;
    }
    cout << "========================================" << endl;
}

int main()
{
    // A dummy queue for starting
    int queue[MAX_QUEUE_LENGTH];

    // The starting ticket number
    int next_ticket_number = 1;

    // Initialize the queue system
    initialize_queue_system(queue);

    // Run the real-time queue system
    while (true)
    {
        cout << "---------------------------------" << endl;
        cout << "Current waiting tickets are:" << endl;
        show_current_queue(queue);

        // 1: take ticket | 2: serve first | 3: cancel ticket | 4: check position | 0: exit
        int operation;
        while (true)
        {
            cout << "Enter an operation (1=take; 2=serve first; 3=cancel; 4=check position; 0=exit):";
            if (cin >> operation)
            {
                if (operation >= 0 && operation <= 4)
                {
                    break;
                }
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input, please re-enter." << endl;
        }

        if (operation == 0)
        {
            break;
        }

        switch (operation)
        {
        case 1:
        {
            bool flag = take_a_queue_ticket(queue, next_ticket_number);
            if (flag)
            {
                cout << "A customer successfully takes a ticket!" << endl;
            }
            else
            {
                cout << "Fail to take a ticket because our queue is already full!" << endl;
            }
            break;
        }
        case 2:
        {
            bool flag = serve_the_first_come_customer(queue);
            if (flag)
            {
                cout << "Successfully serve a customer to go and dine in!" << endl;
            }
            else
            {
                cout << "Fail to serve a customer because no one is waiting in the queue!" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Enter a ticket number to cancel: ";
            int t;
            while (true)
            {
                if (cin >> t && t > 0)
                {
                    break;
                }
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ticket number, please enter a positive integer: ";
            }
            bool flag = cancel_queue_ticket(queue, t);
            if (flag)
            {
                cout << "Successfully cancel the ticket and updated the queue." << endl;
            }
            else
            {
                cout << "Fail to cancel because the ticket is not in the queue!" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "Enter a ticket number to check position: ";
            int t;
            while (true)
            {
                if (cin >> t && t > 0)
                {
                    break;
                }
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ticket number, please enter a positive integer: ";
            }
            int pos = check_position(queue, t);
            if (pos == -1)
            {
                cout << "Ticket #" << t << " is not currently in the queue." << endl;
            }
            else
            {
                cout << "Ticket #" << t << " is currently at position " << pos << " in the queue." << endl;
            }
            break;
        }
        }
    }

    cout << "The queue system close successfully!" << endl;
    return 0;
}