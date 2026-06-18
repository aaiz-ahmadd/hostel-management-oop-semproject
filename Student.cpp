#include "Student.h"
#include <iostream>
using namespace std;
 
Student::Student(String _name, String _id, String _phone, String _roll_no, String _program, int _year) : Person(_name, _id, _phone) {
    roll_no = _roll_no;
    program = _program;
    year = _year;
    room_no = "";
}
 
void Student::displayInfo() {
    cout << "Name: " << getName() << endl;
    cout << "ID: " << getId() << endl;
    cout << "Phone: " << getPhone() << endl;
    cout << "Roll No: " << roll_no << endl;
    cout << "Program: " << program << endl;
    cout << "Year: " << year << endl;
    cout << "Room No: " << room_no << endl;
}
 
String Student::getRollNo() {
    return roll_no;
}
 
void Student::setRoomNo(String _room_no) {
    room_no = _room_no;
}
 
String Student::getRoomNo() {
    return room_no;
}
 
bool Student::operator==(Student& other) {
    return roll_no == other.roll_no;
}

String Student::getProgram(){
    return program;
}

int Student::getYear(){
    return year;
}

void Student::setName(String _name) { Person::setName(_name); }
void Student::setPhone(String _phone) { Person::setPhone(_phone); }
void Student::setProgram(String _program) { program = _program; }
void Student::setYear(int _year) { year = _year; }
 
Student::~Student() {}