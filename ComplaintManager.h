#ifndef COMPLAINTMANAGER_H
#define COMPLAINTMANAGER_H
 
#include "HostelSystem.h"
#include "Complaint.h"
#include "Vector.h"
 
class ComplaintManager : public HostelSystem {
    Vector<Complaint> complaints;
public:
    ComplaintManager(String _name, String _code);
    void run() override;
    void displayMenu() override;
    void fileComplaint(String _student_id, String _issue, String _date);
    void resolveComplaint(int _id);
    void updateStatus(int _id, String _status);
    void displayOpen();
    void displayAll();
    void filterByStudent(String _student_id);
    void saveToFile();
    ~ComplaintManager();
};
 
#endif