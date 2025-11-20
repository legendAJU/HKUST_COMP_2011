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
}

// Destructor
Student::~Student() {
    // TODO:
    // 1. Loop through all added courses and delete them
    // 2. Delete the Course* array itself
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
    addCourse(c);
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
}

// Display all courses and the overall GPA
void Student::displayTranscript() const {
    // TODO:
    // 1. Print "=== Transcript for <name> ==="
    // 2. Loop through all courses and call display()
    // 3. Compute and print GPA (using computeGPA())
}

// ============================================================
// Task 7 – Compute GPA
// ============================================================

// Convert numeric score to GPA points (based on HKUST scale)
double Student::scoreToGPA(double s) const {
    // TODO:
    // Use the mapping provided in the lab description.
    return 0.0;
}

// Compute overall GPA (weighted by credits)
double Student::computeGPA() const {
    // TODO:
    // Compute weighted GPA.
    return 0.0;
}
