#include "Complaint.h"
#include <iostream>
using namespace std;
 
Complaint::Complaint() {
    student_id = "";
    issue = "";
    date = "";
    status = "open";
}
 
Complaint::Complaint(String _student_id, String _issue, String _date) {
    student_id = _student_id;
    issue = _issue;
    date = _date;
    status = "open";
}
 
void Complaint::resolve() {
    status = "resolved";
}
 
void Complaint::updateStatus(String _status) {
    status = _status;
}
 
void Complaint::display() {
    cout << "Student ID: " << student_id << endl;
    cout << "Issue: " << issue << endl;
    cout << "Date: " << date << endl;
    cout << "Status: " << status << endl;
}
 
String Complaint::getStudentId() {
    return student_id;
}
 
String Complaint::getIssue() {
    return issue;
}

String Complaint::getDate() {
    return date;
}

String Complaint::getStatus() {
    return status;
}