#include <iostream>
#include <iomanip>
#include "course.h"
#include "student.h"
using namespace std;

int main() {
    cout << "Welcome to Student GPA Management System!" << endl;
    cout << "Initializing..." << endl;

    string studentName;
    int maxCourses;
    cout << "Enter student name: ";
    cin >> studentName;
    cout << "Enter max number of courses: ";
    cin >> maxCourses;

    Student stu(studentName, maxCourses);

    int option = -1;
    do {
        cout << "======================================" << endl;
        cout << "0. Quit" << endl;
        cout << "1. Add a course" << endl;
        cout << "2. Update a course" << endl;
        cout << "3. Search for a course" << endl;
        cout << "4. Display transcript" << endl;
        cout << "5. Compute GPA" << endl;
        cout << "======================================" << endl;
        cout << "Option: ";
        cin >> option;

        if (option == 1) {  // ===== Add or Auto Replace =====
            string cname;
            int credit;
            double att, assign, mid, fin;
            cout << "Enter course name: ";
            cin >> cname;
            cout << "Enter course credit: ";
            cin >> credit;
            cout << "Enter attendance, assignment, midterm, and final exam scores: ";
            cin >> att >> assign >> mid >> fin;

            Course c(cname, credit, att, assign, mid, fin);
            stu.autoReplace(c); // add normally or auto-delete lowest if full
        }

        else if (option == 2) { // ===== Update =====
            string cname;
            double att, assign, mid, fin;
            cout << "Enter course name to update: ";
            cin >> cname;
            cout << "Enter new scores (attendance, assignment, midterm, final): ";
            cin >> att >> assign >> mid >> fin;
            if (stu.updateCourse(cname, att, assign, mid, fin))
                cout << cname << " updated successfully." << endl;
            else
                cout << "Course not found." << endl;
        }

        else if (option == 3) { // ===== Search =====
            string cname;
            cout << "Enter course name to search: ";
            cin >> cname;
            stu.displayCourse(cname);
        }

        else if (option == 4) { // ===== Display Transcript =====
            stu.displayTranscript();
        }

        else if (option == 5) { // ===== Compute GPA =====
            double gpa = stu.computeGPA();
            cout << "Overall GPA: " << fixed << setprecision(2) << gpa << endl;
        }

        else if (option == 0) {
            cout << "Exiting system..." << endl;
        }

        else {
            cout << "Invalid option. Please try again." << endl;
        }

    } while (option != 0);

    cout << "Program ended. Goodbye!" << endl;
    return 0;
}
