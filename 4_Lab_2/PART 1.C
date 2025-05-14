#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 40
#define MAX_NAME_LEN 50
#define MAX_REG_LEN 20
#define MAX_COURSE_CODE_LEN 20
#define MAX_COURSE_NAME_LEN 50


typedef struct {
    int mark;
    char the_grade;
} Grade;


typedef struct {
    char code[MAX_COURSE_CODE_LEN];
    char name[MAX_COURSE_NAME_LEN];
} Course;


typedef struct {
    char reg_no[MAX_REG_LEN];
    char name[MAX_NAME_LEN];
    int age;
    Course course;
    Grade grade;
} Student;


typedef struct {
    Student students[MAX_STUDENTS];
    int size;
} StudentList;


void initEmptyList(StudentList *list);
void initListWithStudent(StudentList *list, Student s);
void initListFromExisting(StudentList *list, StudentList *existing);
void addStudent(StudentList *list, Student s);
void addStudentAtPosition(StudentList *list, Student s, int pos);
void removeStudent(StudentList *list, Student s);
void removeStudentAtPosition(StudentList *list, int pos);
int getListSize(StudentList *list);
void destroyList(StudentList *list);
void calculateGrade(Student *s);
void printStudent(Student s);
void printList(StudentList *list);

int main() {
    
    StudentList list1;
    initEmptyList(&list1);
    
  
    for (int i = 0; i < 15; i++) {
        Student s;
        snprintf(s.reg_no, MAX_REG_LEN, "REG%03d", i+1);
        snprintf(s.name, MAX_NAME_LEN, "Student %d", i+1);
        s.age = 18 + (i % 5);
        snprintf(s.course.code, MAX_COURSE_CODE_LEN, "CS%d", 101 + (i % 3));
        snprintf(s.course.name, MAX_COURSE_NAME_LEN, "Computer Science %d", 101 + (i % 3));
        s.grade.mark = 50 + (i * 3) % 51; 
        calculateGrade(&s);
        
        addStudent(&list1, s);
    }
    
    printf("Initial list (%d students):\n", getListSize(&list1));
    printList(&list1);
    
  
    Student newStudent;
    strcpy(newStudent.reg_no, "REG100");
    strcpy(newStudent.name, "New Student");
    newStudent.age = 20;
    strcpy(newStudent.course.code, "CS104");
    strcpy(newStudent.course.name, "Advanced Programming");
    newStudent.grade.mark = 85;
    calculateGrade(&newStudent);
    
    addStudentAtPosition(&list1, newStudent, 5);
    printf("\nAfter adding new student at position 5 (%d students):\n", getListSize(&list1));
    printList(&list1);
    
  
    removeStudentAtPosition(&list1, 3);
    printf("\nAfter removing student at position 3 (%d students):\n", getListSize(&list1));
    printList(&list1);
    

    for (int i = 0; i < getListSize(&list1); i++) {
        list1.students[i].grade.mark += 2; 
        if (list1.students[i].grade.mark > 100) {
            list1.students[i].grade.mark = 100;
        }
        calculateGrade(&list1.students[i]);
    }
    printf("\nAfter updating marks (%d students):\n", getListSize(&list1));
    printList(&list1);
    
    destroyList(&list1);
    
    return 0;
}

void initEmptyList(StudentList *list) {
    list->size = 0;
}


void initListWithStudent(StudentList *list, Student s) {
    list->students[0] = s;
    list->size = 1;
}


void initListFromExisting(StudentList *list, StudentList *existing) {
    for (int i = 0; i < existing->size; i++) {
        list->students[i] = existing->students[i];
    }
    list->size = existing->size;
}


void addStudent(StudentList *list, Student s) {
    if (list->size < MAX_STUDENTS) {
        list->students[list->size] = s;
        list->size++;
    } else {
        printf("List is full. Cannot add more students.\n");
    }
}


void addStudentAtPosition(StudentList *list, Student s, int pos) {
    if (pos < 0 || pos > list->size) {
        printf("Invalid position.\n");
        return;
    }
    
    if (list->size >= MAX_STUDENTS) {
        printf("List is full. Cannot add more students.\n");
        return;
    }
    
  
    for (int i = list->size; i > pos; i--) {
        list->students[i] = list->students[i-1];
    }
    
    list->students[pos] = s;
    list->size++;
}


void removeStudent(StudentList *list, Student s) {
    int found = 0;
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->students[i].reg_no, s.reg_no) == 0) {
            found = 1;
            // Shift elements to fill gap
            for (int j = i; j < list->size - 1; j++) {
                list->students[j] = list->students[j+1];
            }
            list->size--;
            break;
        }
    }
    
    if (!found) {
        printf("Student not found.\n");
    }
}


void removeStudentAtPosition(StudentList *list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("Invalid position.\n");
        return;
    }
    
  
    for (int i = pos; i < list->size - 1; i++) {
        list->students[i] = list->students[i+1];
    }
    
    list->size--;
}


int getListSize(StudentList *list) {
    return list->size;
}


void destroyList(StudentList *list) {
    list->size = 0;
}

void calculateGrade(Student *s) {
    if (s->grade.mark > 69) s->grade.the_grade = 'A';
    else if (s->grade.mark > 59) s->grade.the_grade = 'B';
    else if (s->grade.mark > 49) s->grade.the_grade = 'C';
    else if (s->grade.mark > 39) s->grade.the_grade = 'D';
    else s->grade.the_grade = 'E';
}


void printStudent(Student s) {
    printf("Reg: %s, Name: %s, Age: %d, Course: %s (%s), Mark: %d, Grade: %c\n",
           s.reg_no, s.name, s.age, s.course.name, s.course.code, s.grade.mark, s.grade.the_grade);
}


void printList(StudentList *list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d: ", i+1);
        printStudent(list->students[i]);
    }
}