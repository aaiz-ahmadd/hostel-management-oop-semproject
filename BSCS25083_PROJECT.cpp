#include "StudentManager.h"
#include "RoomManager.h"
#include "FeeManager.h"
#include "ComplaintManager.h"
#include "MessManager.h"
#include <iostream>
using namespace std;
 
int main() {
    String code;
    cout << "=== Hostel Management System ===" << endl;
    cout << "Enter Manager Code: ";
    cin >> code;

    const String original_code = "admin123";
    HostelSystem* sys[5];
    sys[0] = new StudentManager("Hostel System", original_code);
    sys[1] = new RoomManager("Hostel System", original_code);
    sys[2] = new FeeManager("Hostel System", original_code);
    sys[3] = new ComplaintManager("Hostel System", original_code);
    sys[4] = new MessManager("Hostel System", original_code);

    if (!sys[0]->verifyCode(code)) {
        cout << "Invalid code. Access denied." << endl;
        for (int i = 0; i < 5; i++)
            delete sys[i];
        return 1;
    }
 
    StudentManager* sm = (StudentManager*)sys[0];
    RoomManager* rm = (RoomManager*)sys[1];
    FeeManager* fm = (FeeManager*)sys[2];
 
    int choice;
    do {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Student Management" << endl;
        cout << "2. Room Management" << endl;
        cout << "3. Fee Management" << endl;
        cout << "4. Complaint Management" << endl;
        cout << "5. Mess Management" << endl;
        cout << "6. Allocate Room to Student" << endl;
        cout << "7. Generate Fees from Rooms" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        cin.ignore(10000, '\n');

        if (choice >= 1 && choice <= 5) {
            sys[choice - 1]->run();
        } else if (choice == 6) {
            String roll_no, room_no;
            cout << "Enter Student Roll No: ";
            cin >> roll_no;
            cin.ignore(10000, '\n');
            cout << "Enter Room No: ";
            cin >> room_no;
            cin.ignore(10000, '\n');
            Student* s = sm->searchStudent(roll_no);
            if (s == nullptr)
                cout << "Student not found." << endl;
            else
                rm->allocateRoom(room_no, s);
        } else if (choice == 7) {
            fm->generateFees(rm->getRooms(), rm->getAllocatedTo());
        }
    } while (choice != 0);
 
    for (int i = 0; i < 5; i++)
        delete sys[i];
 
    return 0;
}