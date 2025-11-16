#include "pa3_task.hpp"
// #include <iostream>
// using namespace std;
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
    int old_capacity = student_management.capacity;
    int new_capacity = 2*old_capacity + 1;

    if(old_capacity == 0 ) // init student management
    {
        student_management.capacity = new_capacity;
        student_management.students = new Student [new_capacity];
    }
    else // find if student is full?
    {
        if(student_management.size == student_management.capacity) // is full
        {
            Student* tempStudents = new Student[new_capacity]; // for copy students
            for (int i = 0; i < student_management.capacity; i++)
            {
                tempStudents[i] = student_management.students[i];
            }
            student_management.capacity = new_capacity;
            delete[] student_management.students;
            student_management.students = tempStudents;
        }
    }
    // 2. initialize new student and assign an ID equal to their position in the array (index-based ID assignment).
    Student* new_student = new Student;
    new_student->id = student_management.size;
    new_student->items = nullptr;
    new_student->items_count = 0;
    new_student->items_capacity = 0;
    // 3. update management information.
    student_management.students[student_management.size] = *new_student;
    student_management.size++;
    student_management.actual_students++;
    // return new student's ID
    return new_student->id;
}

/// Task 2: Add new locker to room management
void add_locker_for_room(RoomManagement& room_management, int room_id, int locker_size) {
    // 0. Validate room_id. If not valid, return.
    if(room_id < 0 || room_id >= room_management.room_count) return;
    // 1. Find room based on room_id.
    Room& target_room = room_management.rooms[room_id];
    //cout<<"Current locker: "<< target_room.locker_list<<endl;
    // 2. Create new locker and locker view.
    Locker* new_locker = new Locker;
    new_locker->item_list = nullptr;
    new_locker->belonged_room = &target_room;
    new_locker->locker_id = target_room.locker_count;
    new_locker->capacity = locker_size;
    new_locker->avaliable_space = locker_size;
    new_locker->item_count = 0;
    LockerView* new_locker_view = new LockerView;
    new_locker_view->locker = new_locker;
    new_locker_view->pre = nullptr;
    new_locker_view->next = nullptr;
    // 3. Insert the new locker view at the correct position of the room's locker linked list.
    if(target_room.locker_list == nullptr) //check whether target room has locker
    {
        target_room.locker_list = new_locker_view;
    }
    else // already has some lockers, sorted by available space, descending, then by id
    {
        
        LockerView* curr_locker =  target_room.locker_list;
        
        while(curr_locker != nullptr)
        {
            if(curr_locker->locker->avaliable_space > new_locker_view->locker->avaliable_space)
            {
                curr_locker = curr_locker->next;
            }
            else if(curr_locker->locker->avaliable_space == new_locker_view->locker->avaliable_space)
            {
                if(curr_locker->locker->locker_id > new_locker_view->locker->locker_id)
                {
                    curr_locker = curr_locker->next;
                }
                else break;
            }
            else break;
        }
        if(curr_locker == nullptr)
        {
            LockerView* tail_locker = target_room.locker_list;
            while(tail_locker != nullptr)
            {
                if(tail_locker->next == nullptr) break;
                tail_locker = tail_locker->next;
            }
            tail_locker->next = new_locker_view;
            new_locker_view->pre = tail_locker;
            new_locker_view->next = nullptr;
        }
        else if (curr_locker->pre == nullptr)
        {
            target_room.locker_list->pre = new_locker_view;
            new_locker_view->next = target_room.locker_list;
            new_locker_view->pre = nullptr;
            target_room.locker_list = new_locker_view;
        }
        else
        {
            curr_locker->pre->next = new_locker_view;
            new_locker_view->pre = curr_locker->pre;
            new_locker_view->next = curr_locker;
            curr_locker->pre = new_locker_view;
        }
    }
    // 4. Update room's information.
    target_room.locker_count++;
    // If successfully added, return true.
    return;
}

/// Task 3: Remove student from student management
void management_remove_student(StudentManagement& all_students, int student_id) {
    // 1. Validate student_id. If not valid, return.
    if(student_id < 0 || student_id >= all_students.size) return;
    if(all_students.students[student_id].id == -1) return;
    // 2. Mark student as deregistered with -1.
    all_students.students[student_id].id = -1;
    // 3. Delete Students' items array.
    delete[] all_students.students[student_id].items;
    all_students.students[student_id].items = nullptr;
    // 4. Update management information.
    all_students.actual_students--;
    return;
}

/// Task 4: Store an item for a student
bool store_item_for_student(StudentManagement& student_management, RoomManagement& room_management,
     int student_id, int item_id, int size) {
    // 1. Find student based on student_id. If student not found, return false.
    //cout<<"Start storeing!!"<<endl;
    if(student_id < 0 || student_id >= student_management.size) return false;
    if(student_management.students[student_id].id == -1) return false;
    Student& target_student = student_management.students[student_id];
    // 2. Find a locker with enough space based on Two-Phase Search Strategy.
    
    // 2.1 Iterates through the student’s items array in order
    // checking each item’s locker for sufficient space (available_space >= item_size). 
    // Selects the FIRST locker that can accommodate the new item.
    Locker* potential_locker = nullptr;
    LockerView* potential_locker_view = nullptr;
    //Phase 1: Existing Lockers
    Item** target_student_items = target_student.items;
    for (int i = 0; i < target_student.items_count; i++)
    {
        if(target_student_items[i]->stored_locker->avaliable_space >= size)
        {
            potential_locker = target_student_items[i]->stored_locker;
            LockerView* curr_locker_list = potential_locker->belonged_room->locker_list;
            while(curr_locker_list != nullptr)
            {
                if(curr_locker_list->locker == potential_locker)
                {
                    potential_locker_view = curr_locker_list;
                    break;
                }
                curr_locker_list = curr_locker_list->next;
            }
            break;
        }
    }
    // 2.2 If no owned locker has space, searches all rooms in ascending order of room ID. 
    // Within each room, traverses the locker linked list from head to tail to find an empty locker.
    // Returns the first empty locker found.
    //Phase 2: Empty Locker Search
    
    if(potential_locker == nullptr)
    {
        
          for (int i = 0; i < room_management.room_count; i++)
          {
            LockerView* curr_locker_list = room_management.rooms[i].locker_list;
            if(curr_locker_list == nullptr) continue;
            else
            {
                while(curr_locker_list != nullptr)
                {
                    if(curr_locker_list->locker->item_count == 0)
                    {
                        potential_locker_view = curr_locker_list;
                        potential_locker = curr_locker_list->locker;
                        break;
                    }
                    curr_locker_list = curr_locker_list->next;
                }
            }
            if(potential_locker != nullptr) break;
          }
    }
    // 2.3 If no such locker is found, the operation fails and returns false.
    if(potential_locker == nullptr) return false;
    //cout<<"We can store !!"<<endl;
    // 3. Create new item.
    Item* new_item = new Item;
    new_item->id = item_id;
    new_item->belonged_student = &target_student;
    new_item->size = size;
    new_item->stored_locker = potential_locker;

    // 4. Store item in locker.
    // 4.1 Creates a new ItemView node and inserts it into the locker’s item_list linked list
    // 4.2 maintaining sorted order by size (ascending) and then by ID as tiebreaker
    //4.1
    ItemView* new_item_view = new ItemView;
    new_item_view->item = new_item;
    new_item_view->prev = nullptr;
    new_item_view->next = nullptr;
    //cout<<"Item view stored is "<< new_item_view<<endl;
    //4.2
    potential_locker->avaliable_space -= new_item_view->item->size;
    if(potential_locker->item_count == 0)
    {
        potential_locker->item_list = new_item_view;
    }
    else
    {
        ItemView* curr_locker_item_list = potential_locker->item_list;
        while (curr_locker_item_list != nullptr)
        {
            if(curr_locker_item_list->item->size < new_item_view->item->size)
            {
                curr_locker_item_list = curr_locker_item_list->next;    
            }
            else if (curr_locker_item_list->item->size == new_item_view->item->size)
            {
                if(curr_locker_item_list->item->id < new_item_view->item->id)
                {
                    curr_locker_item_list = curr_locker_item_list->next;    
                }
                else break;
            }
            else break;
        }
        //insert new_item_view before curr_locker_item_list
        if(curr_locker_item_list == nullptr)
        {
            ItemView* tail_item = potential_locker->item_list;
            while(tail_item != nullptr)
            {
                if(tail_item->next == nullptr) break;
                tail_item = tail_item->next;
            }
            tail_item->next = new_item_view;
            new_item_view->prev = tail_item;
            new_item_view->next = nullptr;
        }
        else if (curr_locker_item_list->prev == nullptr)
        {
            potential_locker->item_list->prev = new_item_view;
            new_item_view->next = potential_locker->item_list;
            new_item_view->prev = nullptr;
            potential_locker->item_list = new_item_view;
        }
        else
        {
            curr_locker_item_list->prev->next = new_item_view;
            new_item_view->prev = curr_locker_item_list->prev;
            new_item_view->next = curr_locker_item_list;
            curr_locker_item_list->prev = new_item_view;
        }
        
    }
    potential_locker->item_count+=1;
    
    // 5. Adjusts the locker’s position in the room’s locker list\
    // sorted by available space (descending) and then by locker ID as a tiebreaker.
    LockerView* curr_room_locker_list = potential_locker_view->next;
    while(curr_room_locker_list != nullptr)
    {
        if(curr_room_locker_list->locker->avaliable_space > potential_locker_view->locker->avaliable_space)
        {
            curr_room_locker_list = curr_room_locker_list->next;

        }
        else if(curr_room_locker_list->locker->avaliable_space == potential_locker_view->locker->avaliable_space)
        {
            if(curr_room_locker_list->locker->locker_id > potential_locker_view->locker->locker_id)
            {
                curr_room_locker_list = curr_room_locker_list->next;
            }
            else break;
        }
        else break;
    }
    // if(curr_room_locker_list != potential_locker_view->next)
    // {
    //     if(curr_room_locker_list->next == nullptr) //last item
    //     {
    //         if(potential_locker_view->pre == nullptr) //potential locker is first item
    //         {
    //             potential_locker_view->next->pre = curr_room_locker_list;
    //             curr_room_locker_list->pre->next = potential_locker_view;
    //             curr_room_locker_list->next = potential_locker_view->next;
    //             potential_locker_view->pre = curr_room_locker_list->pre;
    //             potential_locker_view->next = nullptr;
    //             curr_room_locker_list->pre = nullptr;
    //         }
    //         else
    //         {
    //             potential_locker_view->pre->next = curr_room_locker_list;
    //             potential_locker_view->next->pre = curr_room_locker_list;
    //             curr_room_locker_list->pre->next = potential_locker_view;
    //             curr_room_locker_list->next = potential_locker_view->next;
    //             LockerView** temp_potential_locker_view_pre = &potential_locker_view->pre;
    //             potential_locker_view->pre = curr_room_locker_list->pre;
    //             curr_room_locker_list->pre = *temp_potential_locker_view_pre;
    //             potential_locker_view->next = nullptr;
    //         }
    //     }
    //     else
    //     {
    //         if(potential_locker_view->pre ==nullptr)
    //         {
    //             potential_locker_view->next->pre = curr_room_locker_list;
    //             curr_room_locker_list->pre->next = potential_locker_view;
    //             curr_room_locker_list->next->pre = potential_locker_view;
    //             potential_locker_view->pre = curr_room_locker_list->pre;
    //             LockerView** temp_potential_locker_view_next = &potential_locker_view->next;
    //             potential_locker_view->next = curr_room_locker_list->next;
    //             curr_room_locker_list->next = *temp_potential_locker_view_next;
    //             curr_room_locker_list->pre = nullptr;
    //         }
    //         else
    //         {
    //             potential_locker_view->pre->next = curr_room_locker_list;
    //             potential_locker_view->next->pre = curr_room_locker_list;
    //             curr_room_locker_list->pre->next = potential_locker_view;
    //             curr_room_locker_list->next->pre = potential_locker_view;
    //             LockerView** temp_potential_locker_view_next = &potential_locker_view->next;
    //             LockerView** temp_potential_locker_view_pre = &potential_locker_view->pre;
    //             potential_locker_view->next = curr_room_locker_list->next;
    //             potential_locker_view->pre = curr_room_locker_list->pre;
    //             curr_room_locker_list->pre = *temp_potential_locker_view_pre;
    //             curr_room_locker_list->next = *temp_potential_locker_view_next;
    //         }
    //     }
    // }
    
    if(potential_locker_view->pre == nullptr)
    {
        //potential_locker->belonged_room->locker_list
        if(curr_room_locker_list == nullptr)
        {
            LockerView* tail_locker_view = potential_locker->belonged_room->locker_list;
            while(tail_locker_view!=nullptr)
            {
                if(tail_locker_view->next == nullptr) break;
                tail_locker_view = tail_locker_view->next;
            }
            if(tail_locker_view != potential_locker_view)
            {
            tail_locker_view->next = potential_locker->belonged_room->locker_list;
            potential_locker->belonged_room->locker_list->next->pre = nullptr;
            potential_locker->belonged_room->locker_list->pre = tail_locker_view;
            potential_locker->belonged_room->locker_list = potential_locker->belonged_room->locker_list->next;
            tail_locker_view->next->next = nullptr;
            }
            
        }
        else if(curr_room_locker_list->pre != potential_locker_view)
        {
            curr_room_locker_list->pre->next = potential_locker->belonged_room->locker_list;
            potential_locker->belonged_room->locker_list->pre = curr_room_locker_list->pre;
            potential_locker->belonged_room->locker_list->next->pre = nullptr;
            potential_locker->belonged_room->locker_list = potential_locker->belonged_room->locker_list->next;
            curr_room_locker_list->pre->next->next = curr_room_locker_list;
            curr_room_locker_list->pre = curr_room_locker_list->pre->next;
        }
    }
    else
    {
        if(curr_room_locker_list == nullptr)
        {
            LockerView* tail_locker_view = potential_locker->belonged_room->locker_list;
            while(tail_locker_view!=nullptr)
            {
                if(tail_locker_view->next == nullptr) break;
                tail_locker_view = tail_locker_view->next;
            }
            if(potential_locker_view != tail_locker_view)
            {
                potential_locker_view->pre->next = potential_locker_view->next;
                potential_locker_view->next->pre = potential_locker_view->pre;
                tail_locker_view->next = potential_locker_view;
                potential_locker_view->pre = tail_locker_view;
                potential_locker_view->next = nullptr;
            }
        }
        else if (curr_room_locker_list->pre != potential_locker_view)
        {
            potential_locker_view->pre->next = potential_locker_view->next;
            potential_locker_view->next->pre = potential_locker_view->pre;
            potential_locker_view->pre = curr_room_locker_list->pre;
            potential_locker_view->next = curr_room_locker_list;
            curr_room_locker_list->pre->next = potential_locker_view;
            curr_room_locker_list->pre = potential_locker_view;
        }
    }
    
    // 6. Add item to student's item array.
    // When the item array reaches capacity.
    // allocates a new array with size new_capacity = old_capacity * 2 + 1
    // copies all existing items to the new array
    // deallocates the old array.
    // update new Item and Student information.
    int old_capacity = target_student.items_capacity;
    int new_capacity = 2*old_capacity + 1;
    if(old_capacity == 0)
    {
        target_student.items_capacity = new_capacity;
        target_student.items = new Item* [new_capacity];
    }
    else
    {
        if(target_student.items_capacity == target_student.items_count)
        {
            Item** tempItems = new Item* [new_capacity];
            for (int i = 0; i < target_student.items_capacity; i++)
            {
                tempItems[i] = target_student.items[i];
            }
            target_student.items_capacity = new_capacity;
            delete[] target_student.items;
            target_student.items = tempItems;
        }
    }
    target_student.items[target_student.items_count] = new_item;
    target_student.items_count++;
    


    // 7. Return true to indicate successful storage.
    return true;
}


/// Task 5: Remove an item for a student
bool remove_item_for_student(StudentManagement& student_management, RoomManagement& room_management, int student_id, int item_id) {
    // 1. Find student based on student_id. If student not found, return false.
    if(student_id < 0 || student_id >= student_management.size) return false;
    if(student_management.students[student_id].id == -1) return false;
    Student& target_student = student_management.students[student_id];
    // 2. Find item based on item_id in the student's item array. If item not found, return false.
    Item* target_item = nullptr;
    int target_item_index = 0;
    for (int i = 0; i < target_student.items_count; i++)
    {
        if(target_student.items[i]->id == item_id) 
        {
            target_item = target_student.items[i];
            target_item_index = i;
            break;
        }
    }
    if(target_item == nullptr) return false;

    // 3. Find the locker and room the item is stored in.
    Locker* stored_locker = target_item->stored_locker;
    Room* stored_room = target_item->stored_locker->belonged_room;

    // 4. Remove item from locker.
    // 4.1 Removes the corresponding ItemView node from the locker’s item_list linked
    // 4.2 Updates the locker’s information.
    ItemView* target_item_view = stored_locker->item_list;
    stored_locker->avaliable_space += target_item->size;
    while(target_item_view!=nullptr)
    {
        if(target_item_view->item == target_item)
        {   
            if(target_item_view->prev == nullptr && target_item_view->next == nullptr)
            {
                stored_locker->item_list = nullptr;
                delete target_item_view;
                target_item_view = nullptr;
            }
            else if(target_item_view->prev == nullptr && target_item_view->next != nullptr) //delete head
            {
                target_item_view->next->prev = nullptr;
                stored_locker->item_list = target_item_view->next;
                delete target_item_view;
                target_item_view = nullptr;
            }
            else if (target_item_view->next == nullptr && target_item_view->prev != nullptr) // delete tail
            {
                target_item_view->prev->next = nullptr;
                delete target_item_view;
                target_item_view = nullptr;
            }
            else
            {
            target_item_view->prev->next = target_item_view->next;
            target_item_view->next->prev = target_item_view->prev;
            delete target_item_view;
            target_item_view = nullptr;
            }
            break;
        }
        target_item_view = target_item_view->next;
    }
    stored_locker->item_count--;
    

    // 5. Adjusts the locker’s position in the room’s locker list
    // sorted by available space (descending) and then by locker ID as a tiebreaker.
    //Find stored locker view
    LockerView* stored_locker_view = stored_room->locker_list;
    while(stored_locker_view != nullptr)
    {
        if(stored_locker_view->locker == stored_locker) break;
        stored_locker_view = stored_locker_view->next;
    }
    //Find place to insert
    LockerView* curr_locker_view = stored_locker_view->pre;
    while(curr_locker_view != nullptr)
    {
        if(curr_locker_view->locker->avaliable_space < stored_locker_view->locker->avaliable_space)
        {
            curr_locker_view = curr_locker_view->pre;
        }
        else if (curr_locker_view->locker->avaliable_space == stored_locker_view->locker->avaliable_space)
        {
            if(curr_locker_view->locker->locker_id < stored_locker_view->locker->locker_id)
            {
                curr_locker_view = curr_locker_view->pre;
            }
            else break;
        }
        else break;
    }

    if(stored_locker_view->next == nullptr)
    {
        if(curr_locker_view == nullptr)
        {
            LockerView* head_locker_view = stored_locker_view->locker->belonged_room->locker_list;
            if(head_locker_view != stored_locker_view)
            {
                head_locker_view->pre = stored_locker_view;
                stored_locker_view->pre->next = nullptr;
                stored_locker_view->next = head_locker_view;
                stored_locker_view->pre = nullptr;
                stored_locker_view->locker->belonged_room->locker_list = stored_locker_view;
            }
        }
        else if (curr_locker_view->next != stored_locker_view)
        {
            curr_locker_view->next->pre = stored_locker_view;
            stored_locker_view->pre->next = nullptr;
            stored_locker_view->pre = curr_locker_view;
            stored_locker_view->next = curr_locker_view->next;
            curr_locker_view->next = stored_locker_view;
        }
    }
    else
    {
        if(curr_locker_view == nullptr)
        {
            LockerView* head_locker_view = stored_locker_view->locker->belonged_room->locker_list;
            if(head_locker_view != stored_locker_view)
            {
                stored_locker_view->pre->next = stored_locker_view->next;
                stored_locker_view->next->pre = stored_locker_view->pre;
                stored_locker_view->next = head_locker_view;
                head_locker_view->pre = stored_locker_view;
                stored_locker_view->pre = nullptr;
                stored_locker_view->locker->belonged_room->locker_list = stored_locker_view;
            }
        }
        else if(curr_locker_view->next != stored_locker_view)
        {
            stored_locker_view->pre->next = stored_locker_view->next;
            stored_locker_view->next->pre = stored_locker_view->pre;
            stored_locker_view->pre = curr_locker_view;
            stored_locker_view->next = curr_locker_view->next;
            curr_locker_view->next->pre = stored_locker_view;
            curr_locker_view->next = stored_locker_view;
        }
    }

    // 6. Remove item from student's item array.
    // 6.1 Finds the item in the student's item array.
    // 6.2 Shifts subsequent items to fill the gap.
    // 6.3 Updates the student's item count.
    delete target_item;
    target_item = nullptr;
    for (int i = target_item_index+1; i < target_student.items_count; i++)
    {
        if(target_student.items[i] == nullptr) break;
        target_student.items[i-1] = target_student.items[i];
    }
    target_student.items_count--;
    

    // 7. Deallocates the item.
    // have done yet
    // 8. Returns true to indicate successful removal.
    return true;
}

/// Task 6: Remove a student and clean up all their items
void remove_student(StudentManagement& student_management, RoomManagement& room_management, int student_id) {
    
    // 1. Find student based on student_id.
    Student& target_student = student_management.students[student_id];
    //print_student_status(student_management,student_id);
    // 2. Remove all items belonging to the student.
    // For each item:
    // 2.1 Find the locker and room the item is stored in.
    // 2.2 Remove item from locker.
    // 2.3 Adjusts the locker’s position in the room’s locker list.
    // 2.4 Deallocates the item.
    while(target_student.items_count > 0)
    {
        //cout<<target_student.items_count << endl;
        remove_item_for_student(student_management,room_management,target_student.id,target_student.items[0]->id);
        //cout<<"After deleting one, we have:"<< target_student.items_count<<endl;
    }

    // 3. Remove student from management.
    management_remove_student(student_management,student_id);
    return;
}

/// Task 7: Defragment items for a student
bool defragment_for_student(StudentManagement& student_management, RoomManagement& room_management, int student_id) {
    // 1. Find student based on student_id. If student not found, return false.
    if(student_id < 0 || student_id >= student_management.size) return false;
    if(student_management.students[student_id].id == -1) return false;
    Student& target_student = student_management.students[student_id];
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
    if(room_id < 0 || room_id >= room_management.room_count) return;
    Room& target_room = room_management.rooms[room_id];
    // 2. For each locker in the room:
    //    For each item in the locker:
    //      - Find the student the item belongs to.
    //      - Remove item from student's item array.
    //      - Deallocates the item.
    // LockerView* curr_locker = target_room.locker_list;
    // while(target_room.locker_list != nullptr)
    // {
    //     while(curr_locker->locker->item_count > 0)
    //     {
    //         remove_item_for_student(student_management,room_management,
    //         curr_locker->locker->item_list->item->belonged_student->id,curr_locker->locker->item_list->item->id);
    //     }
        
    // }
    

    // 3. Reset locker information and locker list order.

    return;
}