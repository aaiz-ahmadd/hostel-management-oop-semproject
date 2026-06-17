#include "Fee.h"
#include <iostream>
using namespace std;
 
Fee::Fee() {
    student_id = "";
    amount = 0;
    due_date = "";
    is_paid = false;
}
 
Fee::Fee(String _student_id, float _amount, String _due_date) {
    student_id = _student_id;
    amount = _amount;
    due_date = _due_date;
    is_paid = false;
}
 
void Fee::markPaid() {
    is_paid = true;
}
 
void Fee::display() {
    cout << "Student ID: " << student_id << endl;
    cout << "Amount: " << amount << endl;
    cout << "Due Date: " << due_date << endl;
    if (is_paid)
        cout << "Status: Paid" << endl;
    else
        cout << "Status: Unpaid" << endl;
}
 
String Fee::getStudentId() {
    return student_id;
}

String Fee::getDueDate() {
    return due_date;
}
 
float Fee::getAmount() {
    return amount;
}
 
bool Fee::isPaid() {
    return is_paid;
}