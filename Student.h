#ifndef STUDENT_H
#define STUDENT_H
 
#include "Person.h"
 
class Student : public Person {
    String roll_no;
    String program;
    int year;
    String room_no;
public:
    Student(String _name, String _id, String _phone, String _roll_no, String _program, int _year);
    void displayInfo() override;
    String getRollNo();
    void setRoomNo(String _room_no);
    String getRoomNo();
    bool operator==(Student& other);
    ~Student();
};
 
#endif