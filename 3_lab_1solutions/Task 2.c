#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 40


typedef struct {
    char course_code[20];
    char course_name[50];
} Course;


typedef struct {
    int mark;
    char the_grade;
    int isSet; // 1 = grade set, 0 = not yet
} Grade;


typedef struct {
    char reg_no[20];
    char name[50];
    int age;
    Course course;
    Grade grade;
} Student;


Student students[MAX_STUDENTS];
int studentCount = 0;


char calculateGrade(int mark) {
    if (mark > 69) return 'A';
    else if (mark > 59) return 'B';
    else if (mark > 49) return 'C';
    else if (mark > 39) return 'D';
    else return 'E';
}

// Add student
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students.\n");
        return;
    }

    Student s;

    printf("Enter Reg No: ");
    scanf(" %s", s.reg_no);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Course Code: ");
    scanf(" %s", s.course.course_code);
    printf("Enter Course Name: ");
    scanf(" %[^\n]", s.course.course_name);

    s.grade.isSet = 0; // grade not yet assigned

    students[studentCount++] = s;
    printf("Student added.\n");
}

// Edit student
void editStudent() {
    char reg[20];
    printf("Enter Reg No to Edit: ");
    scanf(" %s", reg);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].reg_no, reg) == 0) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter New Age: ");
            scanf("%d", &students[i].age);
            printf("Enter New Course Code: ");
            scanf(" %s", students[i].course.course_code);
            printf("Enter New Course Name: ");
            scanf(" %[^\n]", students[i].course.course_name);
            printf("Student updated.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

// Assign marks and grade
void assignMarks() {
    char reg[20];
    printf("Enter Reg No to Add Marks: ");
    scanf(" %s", reg);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].reg_no, reg) == 0) {
            if (students[i].grade.isSet) {
                printf("Grade already set: %c. Cannot change.\n", students[i].grade.the_grade);
                return;
            }
            printf("Enter Marks (0-100): ");
            int mark;
            scanf("%d", &mark);
            students[i].grade.mark = mark;
            students[i].grade.the_grade = calculateGrade(mark);
            students[i].grade.isSet = 1;
            printf("Grade assigned: %c\n", students[i].grade.the_grade);
            return;
        }
    }
    printf("Student not found.\n");
}

// Display all students
void showStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n--- Students List ---\n");
    for (int i = 0; i < studentCount; i++) {
        Student s = students[i];
        printf("Reg No: %s\n", s.reg_no);
        printf("Name: %s\n", s.name);
        printf("Age: %d\n", s.age);
        printf("Course: %s (%s)\n", s.course.course_name, s.course.course_code);
        if (s.grade.isSet) {
            printf("Marks: %d, Grade: %c\n", s.grade.mark, s.grade.the_grade);
        } else {
            printf("Grade: Not assigned\n");
        }
        printf("-----------------------\n");
    }
}


int main() {
    int choice;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Add Student\n");
        printf("2. Edit Student\n");
        printf("3. Assign Marks\n");
        printf("4. Show Students\n");
        printf("0. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: editStudent(); break;
            case 3: assignMarks(); break;
            case 4: showStudents(); break;
            case 0: printf("Exiting.\n"); break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}