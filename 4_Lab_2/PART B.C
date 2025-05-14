#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


typedef struct Node {
    Student data;
    struct Node *next;
} Node;


typedef struct {
    Node *head;
    int size;
} StudentLinkedList;


void initLinkedList(StudentLinkedList *list);
void addStudentToLinkedList(StudentLinkedList *list, Student s);
void addStudentAtPositionLinkedList(StudentLinkedList *list, Student s, int pos);
void removeStudentFromLinkedList(StudentLinkedList *list, Student s);
void removeStudentAtPositionLinkedList(StudentLinkedList *list, int pos);
int getLinkedListSize(StudentLinkedList *list);
void destroyLinkedList(StudentLinkedList *list);
void calculateGrade(Student *s);
void printStudent(Student s);
void printLinkedList(StudentLinkedList *list);
Node* createNode(Student s);

int main() {
    StudentLinkedList list;
    initLinkedList(&list);
    
   
    for (int i = 0; i < 15; i++) {
        Student s;
        snprintf(s.reg_no, MAX_REG_LEN, "REG%03d", i+1);
        snprintf(s.name, MAX_NAME_LEN, "Student %d", i+1);
        s.age = 18 + (i % 5);
        snprintf(s.course.code, MAX_COURSE_CODE_LEN, "CS%d", 101 + (i % 3));
        snprintf(s.course.name, MAX_COURSE_NAME_LEN, "Computer Science %d", 101 + (i % 3));
        s.grade.mark = 50 + (i * 3) % 51; // Random marks between 50-100
        calculateGrade(&s);
        
        addStudentToLinkedList(&list, s);
    }
    
    printf("Initial linked list (%d students):\n", getLinkedListSize(&list));
    printLinkedList(&list);
    
   
    Student newStudent;
    strcpy(newStudent.reg_no, "REG100");
    strcpy(newStudent.name, "New Student");
    newStudent.age = 20;
    strcpy(newStudent.course.code, "CS104");
    strcpy(newStudent.course.name, "Advanced Programming");
    newStudent.grade.mark = 85;
    calculateGrade(&newStudent);
    
    addStudentAtPositionLinkedList(&list, newStudent, 5);
    printf("\nAfter adding new student at position 5 (%d students):\n", getLinkedListSize(&list));
    printLinkedList(&list);
    
  
    removeStudentAtPositionLinkedList(&list, 3);
    printf("\nAfter removing student at position 3 (%d students):\n", getLinkedListSize(&list));
    printLinkedList(&list);
    
  
    Node *current = list.head;
    while (current != NULL) {
        current->data.grade.mark += 2; 
        if (current->data.grade.mark > 100) {
            current->data.grade.mark = 100;
        }
        calculateGrade(&current->data);
        current = current->next;
    }
    printf("\nAfter updating marks (%d students):\n", getLinkedListSize(&list));
    printLinkedList(&list);
    
    destroyLinkedList(&list);
    
    return 0;
}


void initLinkedList(StudentLinkedList *list) {
    list->head = NULL;
    list->size = 0;
}


Node* createNode(Student s) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = s;
    newNode->next = NULL;
    return newNode;
}

void addStudentToLinkedList(StudentLinkedList *list, Student s) {
    Node *newNode = createNode(s);
    
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    list->size++;
}


void addStudentAtPositionLinkedList(StudentLinkedList *list, Student s, int pos) {
    if (pos < 0 || pos > list->size) {
        printf("Invalid position.\n");
        return;
    }
    
    Node *newNode = createNode(s);
    
    if (pos == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node *current = list->head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    
    list->size++;
}


void removeStudentFromLinkedList(StudentLinkedList *list, Student s) {
    Node *current = list->head;
    Node *prev = NULL;
    int found = 0;
    
    while (current != NULL) {
        if (strcmp(current->data.reg_no, s.reg_no) == 0) {
            found = 1;
            if (prev == NULL) {
              
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            list->size--;
            break;
        }
        prev = current;
        current = current->next;
    }
    
    if (!found) {
        printf("Student not found.\n");
    }
}


void removeStudentAtPositionLinkedList(StudentLinkedList *list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("Invalid position.\n");
        return;
    }
    
    Node *current = list->head;
    Node *prev = NULL;
    
    if (pos == 0) {
        list->head = current->next;
        free(current);
    } else {
        for (int i = 0; i < pos; i++) {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        free(current);
    }
    
    list->size--;
}


int getLinkedListSize(StudentLinkedList *list) {
    return list->size;
}


void destroyLinkedList(StudentLinkedList *list) {
    Node *current = list->head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    list->head = NULL;
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


void printLinkedList(StudentLinkedList *list) {
    Node *current = list->head;
    int i = 1;
    while (current != NULL) {
        printf("%d: ", i++);
        printStudent(current->data);
        current = current->next;
    }
}