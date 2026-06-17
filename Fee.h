#ifndef FEE_H
#define FEE_H
 
#include "String.h"
 
class Fee {
    String student_id;
    float amount;
    String due_date;
    bool is_paid;
public:
    Fee();
    Fee(String _student_id, float _amount, String _due_date);
    void markPaid();
    void display();
    String getStudentId();
    float getAmount();
    String getDueDate();
    bool isPaid();
};
 
#endif