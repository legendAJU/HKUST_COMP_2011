#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ============================================================
// COMP2011 Lab8: Student GPA Management System
// Task 1 - Define the Course class
// ============================================================
//
// A Course represents a single course record including its name,
// credit, and scores for attendance, assignment, midterm, and final.
// It also stores the weighted total score computed as:
// total = 0.1 * attendance + 0.2 * assignment + 0.3 * midterm + 0.4 * finalExam
//
// ============================================================

class Course {
private:
    string name;         // course name (e.g., COMP2011)
    int credit;          // course credit
    double attendance;   // attendance score
    double assignment;   // assignment score
    double midterm;      // midterm exam score
    double finalExam;    // final exam score
    double total;        // weighted total score

public:
    // ===== Constructors =====
    Course();  // default constructor (initialize all values)
    Course(string n, int c, double att, double asg, double mid, double fin);
    ~Course();                    // destructor

    // ===== Member functions =====

    // Compute weighted total
    void computeTotal();

    // Accessors
    double getTotal() const;   // return weighted total score
    int getCredit() const;     // return credit value
    string getName() const;    // return course name

    // Mutator
    void setScores(double att, double asg, double mid, double fin); // update scores and recompute total

    // Display function for debugging and transcript printing
    void display() const; // Example: COMP2011 (3 credits) - Total: 92.1
};

#endif
