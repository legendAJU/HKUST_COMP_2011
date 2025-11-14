#include "pa3_task.hpp"

/// You can implement Tools functions here.
/// Please make sure all your implementation are included in this file.
/// We will test your code only based on this file.

/// Task 1: Add new student
int add_student(StudentManagement& student_management) {
    // 1. check array capacity
    // When the student array reaches capacity
    // allocates a new array with size new_capacity = old_capacity * 2 + 1
    // copies all existing students to the new array
    // deallocates the old array.

    // 2. initialize new student and assign an ID equal to their position in the array (index-based ID assignment).
    
    // 3. update management information.

    // return new student's ID
    return 0;
}

/// Task 2: Add new locker to room management
void add_locker_for_room(RoomManagement& room_management, int room_id, int locker_size) {
    // 0. Validate room_id. If not valid, return.

    // 1. Find room based on room_id.

    // 2. Create new locker and locker view.

    // 3. Insert the new locker view at the correct position of the room's locker linked list.

    // 4. Update room's information.

    // If successfully added, return true.
    return;
}

/// Task 3: Remove student from student management
void management_remove_student(StudentManagement& all_students, int student_id) {
    // 1. Validate student_id. If not valid, return.

    // 2. Mark student as deregistered with -1.

    // 3. Delete Students' items array.

    // 4. Update management information.
    return;
}

/// Task 4: Store an item for a student
bool store_item_for_student(StudentManagement& student_management, RoomManagement& room_management, int student_id, int item_id, int size) {
    // 1. Find student based on student_id. If student not found, return false.

    // 2. Find a locker with enough space based on Two-Phase Search Strategy.
    
    // 2.1 Iterates through the student’s items array in order
    // checking each item’s locker for sufficient space (available_space >= item_size). 
    // Selects the FIRST locker that can accommodate the new item.

    // 2.2 If no owned locker has space, searches all rooms in ascending order of room ID. 
    // Within each room, traverses the locker linked list from head to tail to find an empty locker.
    // Returns the first empty locker found.

    // 2.3 If no such locker is found, the operation fails and returns false.


    // 3. Create new item.


    // 4. Store item in locker.
    // 4.1 Creates a new ItemView node and inserts it into the locker’s item_list linked list
    // 4.2 maintaining sorted order by size (ascending) and then by ID as tiebreaker

    
    // 5. Adjusts the locker’s position in the room’s locker list\
    // sorted by available space (descending) and then by locker ID as a tiebreaker.
 
    
    // 6. Add item to student's item array.
    // When the item array reaches capacity.
    // allocates a new array with size new_capacity = old_capacity * 2 + 1
    // copies all existing items to the new array
    // deallocates the old array.
    // update new Item and Student information.


    // 7. Return true to indicate successful storage.
    return true;
}


/// Task 5: Remove an item for a student
bool remove_item_for_student(StudentManagement& student_management, RoomManagement& room_management, int student_id, int item_id) {
    // 1. Find student based on student_id. If student not found, return false.


    // 2. Find item based on item_id in the student's item array. If item not found, return false.


    // 3. Find the locker and room the item is stored in.


    // 4. Remove item from locker.
    // 4.1 Removes the corresponding ItemView node from the locker’s item_list linked
    // 4.2 Updates the locker’s information.


    // 5. Adjusts the locker’s position in the room’s locker list
    // sorted by available space (descending) and then by locker ID as a tiebreaker.


    // 6. Remove item from student's item array.
    // 6.1 Finds the item in the student's item array.
    // 6.2 Shifts subsequent items to fill the gap.
    // 6.3 Updates the student's item count.


    // 7. Deallocates the item.

    // 8. Returns true to indicate successful removal.
    return true;
}

/// Task 6: Remove a student and clean up all their items
void remove_student(StudentManagement& student_management, RoomManagement& room_management, int student_id) {
    
    // 1. Find student based on student_id.

    
    // 2. Remove all items belonging to the student.
    // For each item:
    // 2.1 Find the locker and room the item is stored in.
    // 2.2 Remove item from locker.
    // 2.3 Adjusts the locker’s position in the room’s locker list.
    // 2.4 Deallocates the item.


    // 3. Remove student from management.
    return;
}

/// Task 7: Defragment items for a student
bool defragment_for_student(StudentManagement& student_management, RoomManagement& room_management, int student_id) {
    // 1. Find student based on student_id. If student not found, return false.


    // 2. Take all items from their current lockers WITHOUT deletion
    // 2.1 For each item, find the locker and room the item is stored in.
    // 2.2 Take item from locker.
    // 2.3 Adjusts the locker’s position in the room’s locker list.


    // 3. Find empty lockers and put items based on Greedy Packing Algorithm
    // Greedy Packing Algorithm:
    // Find an empty locker.
    // While items remain unpacked:
    //   Searches through all unpacked items
    //   Selects the LARGEST item that can be stored in the current locker.
    //   If tied on size, selects the one with the larger Item ID 
    //   Store the selected item into the current locker
    //   If no items fit in the current locker:
    //     Maintain Locker list order
    //     Acquires a new empty locker
    //     Continues packing remaining items


    // 4. return true to indicate successful defragmentation.
    return true;
}

/// Task 8: Clean up all items for a room
void cleanup_for_room(StudentManagement& student_management, RoomManagement& room_management, int room_id) {
    // 1. Find room based on room_id. if room not found, return.


    // 2. For each locker in the room:
    //    For each item in the locker:
    //      - Find the student the item belongs to.
    //      - Remove item from student's item array.
    //      - Deallocates the item.


    // 3. Reset locker information and locker list order.

    return;
}