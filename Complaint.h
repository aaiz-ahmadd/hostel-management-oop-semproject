#ifndef COMPLAINT_H
#define COMPLAINT_H
 
#include "String.h"
 
class Complaint {
    String student_id;
    String issue;
    String status;
    String date;
public:
    Complaint(String _student_id, String _issue, String _date);
    void resolve();
    void updateStatus(String _status);
    void display();
    String getStudentId();
    String getStatus();
};
 
#endif