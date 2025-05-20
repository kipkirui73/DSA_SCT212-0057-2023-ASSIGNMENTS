#include <iostream>
#include <string>
using namespace std;

class Course {
public:
    string course_code;
    string course_name;

    Course(string code = "", string name = "") : course_code(code), course_name(name) {}
};

class Grade {
private:
    int mark;
    char the_grade;
    bool isSet;

    char calculateGrade(int mark) {
        if (mark > 69) return 'A';
        if (mark > 59) return 'B';
        if (mark > 49) return 'C';
        if (mark > 39) return 'D';
        return 'E';
    }

public:
    Grade() : mark(0), the_grade('E'), isSet(false) {}

    void setMark(int m) {
        if (m < 0 || m > 100) {
            cout << "Invalid mark! Must be between 0-100.\n";
            return;
        }
        
        if (!isSet) {
            mark = m;
            the_grade = calculateGrade(mark);
            isSet = true;
            cout << "Grade set: " << the_grade << endl;
        } else {
            cout << "Grade already set and cannot be changed.\n";
        }
    }

    int getMark() const { return mark; }
    char getGrade() const { return the_grade; }
    bool isGradeSet() const { return isSet; }
};

class Student {
private:
    string reg_no;
    string name;
    int age;
    Course course;
    Grade grade;

public:
    void inputDetails() {
        cout << "\n--- Enter Student Details ---\n";
        cout << "Registration number: ";
        getline(cin, reg_no);

        cout << "Name: ";
        getline(cin, name);

        while (true) {
            cout << "Age: ";
            cin >> age;
            if (age > 0 && age < 120) break;
            cout << "Invalid age! Please enter between 1-119.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Course code: ";
        cin >> course.course_code;

        cout << "Course name: ";
        cin.ignore();
        getline(cin, course.course_name);
    }

    void editDetails() {
        cout << "\n--- Edit Student Details ---\n";
        cout << "Name (" << name << "): ";
        string new_name;
        getline(cin, new_name);
        if (!new_name.empty()) name = new_name;

        while (true) {
            cout << "Age (" << age << "): ";
            string input;
            getline(cin, input);
            if (input.empty()) break;
            try {
                int new_age = stoi(input);
                if (new_age > 0 && new_age < 120) {
                    age = new_age;
                    break;
                }
                cout << "Invalid age! Please enter between 1-119.\n";
            } catch (...) {
                cout << "Please enter a valid number.\n";
            }
        }

        cout << "Course code (" << course.course_code << "): ";
        string new_code;
        getline(cin, new_code);
        if (!new_code.empty()) course.course_code = new_code;

        cout << "Course name (" << course.course_name << "): ";
        string new_course_name;
        getline(cin, new_course_name);
        if (!new_course_name.empty()) course.course_name = new_course_name;
    }

    void assignMarks() {
        if (grade.isGradeSet()) {
            cout << "Grade already assigned: " << grade.getGrade() << endl;
            return;
        }

        int mark;
        while (true) {
            cout << "Enter marks (0-100): ";
            cin >> mark;
            if (mark >= 0 && mark <= 100) {
                grade.setMark(mark);
                break;
            }
            cout << "Invalid marks! Please enter between 0-100.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    void display() const {
        cout << "\n--- Student Details ---\n";
        cout << "Reg No: " << reg_no << "\nName: " << name << "\nAge: " << age;
        cout << "\nCourse: " << course.course_name << " (" << course.course_code << ")";
        if (grade.isGradeSet())
            cout << "\nMark: " << grade.getMark() << " | Grade: " << grade.getGrade() << endl;
        else
            cout << "\nGrade: Not assigned yet\n";
    }

    string getRegNo() const {
        return reg_no;
    }
};

int main() {
    const int MAX = 40;
    Student students[MAX];
    int count = 0;
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n2. Edit Student\n3. Assign Marks\n4. Display All\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            if (count < MAX) {
                students[count].inputDetails();
                count++;
            } else {
                cout << "Maximum number of students reached!\n";
            }
        } else if (choice == 2) {
            if (count == 0) {
                cout << "No students available to edit.\n";
                continue;
            }
            
            string reg;
            cout << "Enter registration number to edit: ";
            getline(cin, reg);

            bool found = false;
            for (int i = 0; i < count; i++) {
                if (students[i].getRegNo() == reg) {
                    students[i].editDetails();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Student not found!\n";
        } else if (choice == 3) {
            if (count == 0) {
                cout << "No students available.\n";
                continue;
            }
            
            string reg;
            cout << "Enter registration number to assign marks: ";
            getline(cin, reg);

            bool found = false;
            for (int i = 0; i < count; i++) {
                if (students[i].getRegNo() == reg) {
                    students[i].assignMarks();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Student not found!\n";
        } else if (choice == 4) {
            if (count == 0) {
                cout << "No students to display.\n";
            } else {
                cout << "\n--- All Students ---\n";
                for (int i = 0; i < count; i++) {
                    students[i].display();
                    cout << "-------------------\n";
                }
            }
        } else if (choice == 0) {
            cout << "Exiting program...\n";
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}