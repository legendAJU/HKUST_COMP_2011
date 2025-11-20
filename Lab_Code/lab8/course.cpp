#include "course.h"

// ============================================================
// COMP2011 Lab8: Student GPA Management System
// Implementation of Course class (Task 1)
// ============================================================

// ===== Default constructor =====
Course::Course() {
    credit = 0;
    attendance = 0.0;
    assignment = 0.0;
    midterm = 0.0;
    finalExam = 0.0;
    total = 0.0;
}

// ===== Parameterized constructor =====
Course::Course(string n, int c, double att, double asg, double mid, double fin) {
    // TODO:
    // 1. assign all parameters to member variables
    // 2. call computeTotal() to calculate weighted score
}

// ===== Destructor =====
Course::~Course() {
    // No dynamic allocation inside Course,
    // but still define for completeness
}

// ============================================================
// Member function implementations
// ============================================================

// ===== Compute weighted total =====
void Course::computeTotal() {
    // TODO: compute weighted total and store in total
}

// ===== Accessors =====
double Course::getTotal() const {
    // TODO: return total
    return 0.0;
}

int Course::getCredit() const {
    // TODO: return credit
    return 0;
}

string Course::getName() const {
    // TODO: return name
    return "";
}

// ===== Mutator =====
// Update scores and recompute weighted total
void Course::setScores(double att, double asg, double mid, double fin) {
    // TODO:
    // 1. update attendance, assignment, midterm, finalExam
    // 2. call computeTotal()
}

// ===== Display function =====
// Print course summary, e.g.:
// COMP2011 (3 credits) - Total: 92.1
void Course::display() const {
    // TODO: print name, credits, and total (1 decimal place)
}
