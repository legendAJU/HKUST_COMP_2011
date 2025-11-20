#include "student.h"
#include <iomanip>



// ============================================================
// COMP2011 Lab 8 – Student GPA Management System
// Implementation of Student class (Tasks 2–7)
// ============================================================

// ============================================================
// Task 2 – Constructor / Destructor
// ============================================================

// Constructor
Student::Student(string n, int cap) {
    // TODO:
    // 1. Initialize name and capacity
    // 2. Set courseCount = 0
    // 3. Allocate a dynamic array of Course* (size = capacity)
    // 4. Initialize all pointers to nullptr
    name  = n;
    capacity = cap;
    courseCount = 0;
    courses = new Course*[capacity];
    for (int i = 0; i < capacity; i++)
    {
        courses[i] = nullptr;
    }
}

// Destructor
Student::~Student() {
    // TODO:
    // 1. Loop through all added courses and delete them
    // 2. Delete the Course* array itself
    for (int i = 0; i < capacity; i++)
    {
        delete courses[i];
        courses[i] = nullptr;
    }
    delete [] courses;
    courses = nullptr;
}

// ============================================================
// Task 3 – Add a Course (Create)
// ============================================================

void Student::addCourse(const Course &c) {
    // TODO:
    // 1. Check if courseCount == capacity → cannot add more (course list full)
    // 2. Otherwise create a new Course object using copy constructor
    // 3. Store its pointer in the array
    // 4. Increase courseCount
    if(courseCount == capacity) return;
    courses[courseCount] = new Course(c);
    cout<<"Course "<< courses[courseCount]->getName() << " added successfully."<<endl;
    courseCount++;
    
}

// ============================================================
// Task 4 – Auto Delete (Replace Lowest when Full)
// ============================================================

void Student::autoReplace(const Course &c) {
    // TODO:
    // 1. If courseCount < capacity → simply call addCourse(c)
    // 2. Otherwise:
    //   a. Find the course with the lowest total score
    //   b. Delete that course (free memory)
    //   c. Replace it with a new Course (c)
    //   d. Print a message showing which course was dropped
    if (courseCount < capacity) addCourse(c);
    else
    {
        int index = 0;
        for (int i = 1; i < courseCount; i++)
        {
            if(courses[i]->getTotal() < courses[index]->getTotal()) index = i;
        }
        cout<<"Course list full. Dropped lowest course: "<< courses[index]->getName()<<" (Total "<<courses[index]->getTotal()<<")"<<endl;
        delete courses[index];
        courses[index] = new Course(c);
    }
}

// ============================================================
// Task 5 – Edit a Course (Update)
// ============================================================

bool Student::updateCourse(string cname,
                          double att, double asg, double mid, double fin) {
    // TODO:
    // 1. Loop through all courses
    // 2. If course name matches:
    //    a. Call setScores(att, asg, mid, fin)
    //    b. Return true
    // 3. If not found → return false
    for (int i = 0; i < courseCount; i++)
    {
        if(courses[i]->getName() == cname)
        {
            courses[i]->setScores(att,asg,mid,fin); return true;
        }
    }
    return false;
}

// ============================================================
// Task 6 – Search and Display (Read)
// ============================================================

// Display a specific course by name
void Student::displayCourse(string cname) const {
    // TODO:
    // 1. Search for the course name
    // 2. If found → call its display()
    // 3. Otherwise print "Course not found."
    for (int i = 0; i < courseCount; i++)
    {
        if(courses[i]->getName() == cname)
        {
            courses[i]->display(); return;
        }
    }
    cout<<"Course not found."<<endl;    
}

// Display all courses and the overall GPA
void Student::displayTranscript() const {
    // TODO:
    // 1. Print "=== Transcript for <name> ==="
    // 2. Loop through all courses and call display()
    // 3. Compute and print GPA (using computeGPA())
    cout<<"=== Transcript for "<<name<<" ==="<<endl;
    for (int i = 0; i < courseCount; i++)
    {
        courses[i]->display();
    } 
    cout<<"Overall GPA: "<<fixed << setprecision(2)<<computeGPA()<<endl;
}

// ============================================================
// Task 7 – Compute GPA
// ============================================================

// Convert numeric score to GPA points (based on HKUST scale)
double Student::scoreToGPA(double s) const {
    // TODO:
    // Use the mapping provided in the lab description.
    
    if (s >= 95) return 4.3;
    else if (s >= 90) return 4;
    else if (s >= 85) return 3.7;
    else if (s >= 80) return 3.3;
    else if (s >= 75) return 3.0;
    else if (s >= 70) return 2.7;
    else if (s >= 65) return 2.3;
    else if (s >= 60) return 2.0;
    else if (s >= 55) return 1.7;
    else if (s >= 50) return 1.0;
    else return 0;
    
}

// Compute overall GPA (weighted by credits)
double Student::computeGPA() const {
    // TODO:
    // Compute weighted GPA.
    int total_credits = 0;
    double total_GPA = 0.0;
    for (int i = 0; i < courseCount; i++)
    {
        total_credits += courses[i]->getCredit();
        total_GPA += scoreToGPA(courses[i]->getTotal()) * courses[i]->getCredit(); 
    }
    if(total_credits > 0) return total_GPA / total_credits;
    return 0.0;
}
