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
    cout << "8. Load from File" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
}
 
void ComplaintManager::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); choice = -1; continue; }
        cin.ignore(10000, '\n');
        if (choice == 1) {
            String student_id, issue, date;
            cout << "Enter Student Roll No: ";
            cin >> student_id;
            cin.ignore(10000, '\n');
            cout << "Enter Issue: ";
            issue.getline(cin, '\n');
            cout << "Enter Date (DD/MM/YYYY): ";
            cin >> date;
            cin.ignore(10000, '\n');
            fileComplaint(student_id, issue, date);
        } else if (choice == 2) {
            int id;
            cout << "Enter Complaint ID (starting from 1): ";
            cin >> id;
            cin.ignore(10000, '\n');
            resolveComplaint(id - 1);
        } else if (choice == 3) {
            int id;
            String status;
            cout << "Enter Complaint ID (starting from 1): ";
            cin >> id;
            cin.ignore(10000, '\n');
            cout << "Enter New Status (open/in-progress/resolved): ";
            cin >> status;
            cin.ignore(10000, '\n');
            updateStatus(id - 1, status);
        } else if (choice == 4) {
            displayOpen();
        } else if (choice == 5) {
            displayAll();
        } else if (choice == 6) {
            String student_id;
            cout << "Enter Student Roll No: ";
            cin >> student_id;
            cin.ignore(10000, '\n');
            filterByStudent(student_id);
        } else if (choice == 7) {
            saveToFile();
        } else if (choice == 8) {
            loadFromFile();
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
            cout << "\n--- Complaint " << i + 1 << " ---" << endl;
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
        cout << "\n--- Complaint " << i + 1 << " ---" << endl;
        complaints[i].display();
    }
}
 
void ComplaintManager::filterByStudent(String _student_id) {
    bool found = false;
    for (int i = 0; i < complaints.size(); i++) {
        if (complaints[i].getStudentId() == _student_id) {
            cout << "\n--- Complaint " << i + 1 << " ---" << endl;
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
        file << complaints[i].getStudentId() << "\t"
             << complaints[i].getIssue() << "\t"
             << complaints[i].getDate() << "\t"
             << complaints[i].getStatus() << "\n";
    }
    file.close();
    cout << "Saved to file." << endl;
}
 
void ComplaintManager::loadFromFile() {
    ifstream file("complaints.txt");
    if (!file.is_open()) {
        cout << "File not found." << endl;
        return;
    }
    complaints.clear();
    String line;
    while (true) {
        line.getline(file, '\n');
        if (line.empty())
            break;
        int count = 0;
        String* parts = line.split('\t', count);
        if (count >= 4) {
            Complaint c(parts[0], parts[1], parts[2]);
            c.updateStatus(parts[3]);
            complaints.push_back(c);
        }
        delete[] parts;
    }
    file.close();
    cout << "Loaded from file." << endl;
}

ComplaintManager::~ComplaintManager() {}