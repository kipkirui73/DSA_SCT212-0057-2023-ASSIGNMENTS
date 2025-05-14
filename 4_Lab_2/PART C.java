import java.util.Scanner;

class Grade {
    private int mark;
    private char grade;

    public Grade() {
        this.mark = 0;
        this.grade = 'E';
    }

    public void setMark(int mark) {
        if (mark >= 0 && mark <= 100) {
            this.mark = mark;
            calculateGrade();
        }
    }

    public int getMark() {
        return mark;
    }

    public char getGrade() {
        return grade;
    }

    private void calculateGrade() {
        if (mark > 69) grade = 'A';
        else if (mark > 59) grade = 'B';
        else if (mark > 49) grade = 'C';
        else if (mark > 39) grade = 'D';
        else grade = 'E';
    }
}

class Course {
    private String code;
    private String name;

    public Course(String code, String name) {
        this.code = code;
        this.name = name;
    }

    public String getCode() {
        return code;
    }

    public String getName() {
        return name;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public void setName(String name) {
        this.name = name;
    }
}

class Student {
    private String regNo;
    private String name;
    private int age;
    private Course course;
    private Grade grade;

    public Student(String regNo, String name, int age, Course course) {
        this.regNo = regNo;
        this.name = name;
        this.age = age;
        this.course = course;
        this.grade = new Grade();
    }

    
    public String getRegNo() { return regNo; }
    public String getName() { return name; }
    public int getAge() { return age; }
    public Course getCourse() { return course; }
    public Grade getGrade() { return grade; }

    public void setMark(int mark) {
        grade.setMark(mark);
    }

    public void printDetails() {
        System.out.printf("Reg: %s, Name: %s, Age: %d, Course: %s (%s), Mark: %d, Grade: %c\n",
                regNo, name, age, course.getName(), course.getCode(), grade.getMark(), grade.getGrade());
    }
}

class Node {
    Student data;
    Node next;

    public Node(Student data) {
        this.data = data;
        this.next = null;
    }
}

class StudentLinkedList {
    private Node head;
    private int size;

    public StudentLinkedList() {
        head = null;
        size = 0;
    }

    public void addStudent(Student student) {
        Node newNode = new Node(student);
        if (head == null) {
            head = newNode;
        } else {
            Node current = head;
            while (current.next != null) {
                current = current.next;
            }
            current.next = newNode;
        }
        size++;
    }

    public void addStudentAtPosition(Student student, int position) {
        if (position < 0 || position > size) {
            System.out.println("Invalid position");
            return;
        }

        Node newNode = new Node(student);
        if (position == 0) {
            newNode.next = head;
            head = newNode;
        } else {
            Node current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current.next;
            }
            newNode.next = current.next;
            current.next = newNode;
        }
        size++;
    }

    public void removeStudent(String regNo) {
        if (head == null) return;

        if (head.data.getRegNo().equals(regNo)) {
            head = head.next;
            size--;
            return;
        }

        Node current = head;
        while (current.next != null && !current.next.data.getRegNo().equals(regNo)) {
            current = current.next;
        }

        if (current.next != null) {
            current.next = current.next.next;
            size--;
        }
    }

    public void removeStudentAtPosition(int position) {
        if (position < 0 || position >= size) {
            System.out.println("Invalid position");
            return;
        }

        if (position == 0) {
            head = head.next;
        } else {
            Node current = head;
            for (int i = 0; i < position - 1; i++) {
                current = current.next;
            }
            current.next = current.next.next;
        }
        size--;
    }

    public Student getStudent(String regNo) {
        Node current = head;
        while (current != null) {
            if (current.data.getRegNo().equals(regNo)) {
                return current.data;
            }
            current = current.next;
        }
        return null;
    }

    public int getSize() {
        return size;
    }

    public void printAllStudents() {
        Node current = head;
        int count = 1;
        while (current != null) {
            System.out.print(count++ + ": ");
            current.data.printDetails();
            current = current.next;
        }
    }
}

public class StudentManagementSystem {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        StudentLinkedList studentList = new StudentLinkedList();

        for (int i = 1; i <= 5; i++) {
            Course course = new Course("CS" + (100 + i), "Computer Science " + i);
            Student student = new Student("REG" + i, "Student " + i, 18 + i, course);
            student.setMark(50 + (i * 5));
            studentList.addStudent(student);
        }

        while (true) {
            System.out.println("\nStudent Management System");
            System.out.println("1. Add Student");
            System.out.println("2. Edit Student Marks");
            System.out.println("3. Remove Student");
            System.out.println("4. Display All Students");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine(); 

            switch (choice) {
                case 1:
                    System.out.print("Enter registration number: ");
                    String regNo = scanner.nextLine();
                    System.out.print("Enter name: ");
                    String name = scanner.nextLine();
                    System.out.print("Enter age: ");
                    int age = scanner.nextInt();
                    scanner.nextLine();
                    System.out.print("Enter course code: ");
                    String code = scanner.nextLine();
                    System.out.print("Enter course name: ");
                    String courseName = scanner.nextLine();
                    System.out.print("Enter mark: ");
                    int mark = scanner.nextInt();
                    scanner.nextLine();

                    Course course = new Course(code, courseName);
                    Student student = new Student(regNo, name, age, course);
                    student.setMark(mark);
                    studentList.addStudent(student);
                    System.out.println("Student added successfully!");
                    break;

                case 2:
                    System.out.print("Enter registration number to edit marks: ");
                    String editRegNo = scanner.nextLine();
                    Student editStudent = studentList.getStudent(editRegNo);
                    if (editStudent != null) {
                        System.out.print("Enter new mark: ");
                        int newMark = scanner.nextInt();
                        scanner.nextLine();
                        editStudent.setMark(newMark);
                        System.out.println("Marks updated successfully!");
                    } else {
                        System.out.println("Student not found!");
                    }
                    break;

                case 3:
                    System.out.print("Enter registration number to remove: ");
                    String removeRegNo = scanner.nextLine();
                    studentList.removeStudent(removeRegNo);
                    System.out.println("Student removed successfully!");
                    break;

                case 4:
                    System.out.println("\nAll Students (" + studentList.getSize() + "):");
                    studentList.printAllStudents();
                    break;

                case 5:
                    System.out.println("Exiting program...");
                    scanner.close();
                    System.exit(0);

                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        }
    }
}