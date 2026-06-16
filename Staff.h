#ifndef STAFF_H
#define STAFF_H
 
#include "Person.h"
 
class Staff : public Person {
    String employee_id;
    String role;
    String shift;
    float salary;
public:
    Staff(String _name, String _id, String _phone, String _employee_id, String _role, String _shift, float _salary);
    void displayInfo() override;
    String getEmployeeId();
    String getRole();
    String getShift();
    float getSalary();
    ~Staff();
};
 
#endif