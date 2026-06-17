#include "ComplaintManager.h"
#include <iostream>
#include <fstream>
using namespace std;
 
ComplaintManager::ComplaintManager(String _name, String _code) : HostelSystem(_name, _code) {}
 
void ComplaintManager::displayMenu() {
    cout << "\n=== Complaint Manager ===" << endl;
    cout << "1. File Complaint" << endl;
    cout << "2. Resolve Complaint" << endl;
    cout << "3. Update Status" << endl;
    cout << "4. Display Open Complaints" << endl;
    cout << "5. Display All Complaints" << endl;
    cout << "6. Filter by Student" << endl;
    cout << "7. Save to File" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
}
 
void ComplaintManager::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        if (choice == 1) {
            String student_id, issue, date;
            cout << "Enter Student ID: ";
            cin >> student_id;
            cout << "Enter Issue: ";
            cin >> issue;
            cout << "Enter Date: ";
            cin >> date;
            fileComplaint(student_id, issue, date);
        } else if (choice == 2) {
            int id;
            cout << "Enter Complaint ID: ";
            cin >> id;
            resolveComplaint(id);
        } else if (choice == 3) {
            int id;
            String status;
            cout << "Enter Complaint ID: ";
            cin >> id;
            cout << "Enter New Status: ";
            cin >> status;
            updateStatus(id, status);
        } else if (choice == 4) {
            displayOpen();
        } else if (choice == 5) {
            displayAll();
        } else if (choice == 6) {
            String student_id;
            cout << "Enter Student ID: ";
            cin >> student_id;
            filterByStudent(student_id);
        } else if (choice == 7) {
            saveToFile();
        }
    } while (choice != 0);
}
 
void ComplaintManager::fileComplaint(String _student_id, String _issue, String _date) {
    complaints.push_back(Complaint(_student_id, _issue, _date));
    cout << "Complaint filed successfully." << endl;
}
 
void ComplaintManager::resolveComplaint(int _id) {
    if (_id < 0 || _id >= complaints.size()) {
        cout << "Invalid ID." << endl;
        return;
    }
    complaints[_id].resolve();
    cout << "Complaint resolved." << endl;
}
 
void ComplaintManager::updateStatus(int _id, String _status) {
    if (_id < 0 || _id >= complaints.size()) {
        cout << "Invalid ID." << endl;
        return;
    }
    complaints[_id].updateStatus(_status);
    cout << "Status updated." << endl;
}
 
void ComplaintManager::displayOpen() {
    bool found = false;
    for (int i = 0; i < complaints.size(); i++) {
        if (complaints[i].getStatus() == "open") {
            cout << "\n--- Complaint " << i << " ---" << endl;
            complaints[i].display();
            found = true;
        }
    }
    if (!found)
        cout << "No open complaints." << endl;
}
 
void ComplaintManager::displayAll() {
    if (complaints.size() == 0) {
        cout << "No complaints found." << endl;
        return;
    }
    for (int i = 0; i < complaints.size(); i++) {
        cout << "\n--- Complaint " << i << " ---" << endl;
        complaints[i].display();
    }
}
 
void ComplaintManager::filterByStudent(String _student_id) {
    bool found = false;
    for (int i = 0; i < complaints.size(); i++) {
        if (complaints[i].getStudentId() == _student_id) {
            cout << "\n--- Complaint " << i << " ---" << endl;
            complaints[i].display();
            found = true;
        }
    }
    if (!found)
        cout << "No complaints found for this student." << endl;
}
 
void ComplaintManager::saveToFile() {
    ofstream file("complaints.txt");
    for (int i = 0; i < complaints.size(); i++) {
        file << complaints[i].getStudentId() << "\n";
        file << complaints[i].getStatus() << "\n";
    }
    file.close();
    cout << "Saved to file." << endl;
}
 
ComplaintManager::~ComplaintManager() {}