#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "course.h"
using namespace std;

// ============================================================
// COMP2011 Lab8: Student GPA Management System
// Implementation of Student class (Tasks 2–7)
// ============================================================
//
// The Student class manages multiple Course objects using a
// dynamically allocated array of Course pointers.
//
// Each Task builds upon this class step by step:
//   - Task 2: Constructor / Destructor with dynamic memory
//   - Task 3: Add a Course
//   - Task 4: Auto Delete (replace lowest when full)
//   - Task 5: Update Course scores
//   - Task 6: Search and Display courses
//   - Task 7: Compute GPA
//
// ============================================================

class Student {
private:
    string name;        // student's name
    Course **courses;   // dynamic array of Course pointers
    int courseCount;    // current number of added courses
    int capacity;       // maximum number of courses allowed

public:
    // ===== Constructor / Destructor =====
    Student(string n, int cap);      // TODO: allocate memory for Course* array
    ~Student();                      // TODO: release memory

    // ===== Core functionalities =====
    void addCourse(const Course &c);        // Task 3: Add a course (no overflow)
    void autoReplace(const Course &c);      // Task 4: Add with auto delete lowest 
    bool updateCourse(string cname,
                      double att, double asg, double mid, double fin); // Task 5: Update
    void displayCourse(string cname) const; // Task 6: Display single course
    void displayTranscript() const;         // Task 6: Display all courses and GPA
    double computeGPA() const;              // Task 7: Compute weighted GPA

private:
    // ===== Helper functions =====
    double scoreToGPA(double score) const;  // convert numeric score to GPA (Task 7)
};

#endif
