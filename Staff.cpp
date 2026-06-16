#include "Staff.h"
#include <iostream>
using namespace std;
 
Staff::Staff(String _name, String _id, String _phone, String _employee_id, String _role, String _shift, float _salary) : Person(_name, _id, _phone) {
    employee_id = _employee_id;
    role = _role;
    shift = _shift;
    salary = _salary;
}
 
void Staff::displayInfo() {
    cout << "Name: " << getName() << endl;
    cout << "ID: " << getId() << endl;
    cout << "Phone: " << getPhone() << endl;
    cout << "Employee ID: " << employee_id << endl;
    cout << "Role: " << role << endl;
    cout << "Shift: " << shift << endl;
    cout << "Salary: " << salary << endl;
}
 
String Staff::getEmployeeId() {
    return employee_id;
}
 
String Staff::getRole() {
    return role;
}
 
String Staff::getShift() {
    return shift;
}
 
float Staff::getSalary() {
    return salary;
}
 
Staff::~Staff() {}