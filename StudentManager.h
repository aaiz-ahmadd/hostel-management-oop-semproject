#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H
 
#include "HostelSystem.h"
#include "Student.h"
#include "Vector.h"
 
class StudentManager : public HostelSystem {
    Vector<Student*> students;
public:
    StudentManager(String _name, String _code);
    void run() override;
    void displayMenu() override;
    void addStudent();
    void removeStudent(String _roll_no);
    Student* searchStudent(String _roll_no);
    void updateStudent(String _roll_no);
    void sortStudents();
    void displayAll();
    void saveToFile();
    void loadFromFile();
    ~StudentManager();
};
 
#endif