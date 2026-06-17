#ifndef FEEMANAGER_H
#define FEEMANAGER_H
 
#include "HostelSystem.h"
#include "Fee.h"
#include "Room.h"
#include "Vector.h"
 
class FeeManager : public HostelSystem {
    Vector<Fee> fees;
public:
    FeeManager(String _name, String _code);
    void run() override;
    void displayMenu() override;
    void generateFees(Vector<Room*>& _rooms);
    void generateFeeForStudent(String _student_id, float _amount, String _due_date);
    void markPaid(String _student_id);
    void displayPending();
    void displayAll();
    void displayByStudent(String _student_id);
    float calcTotalDue();
    void saveToFile();
    ~FeeManager();
};
 
#endif