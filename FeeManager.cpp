#include "FeeManager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
 
FeeManager::FeeManager(String _name, String _code) : HostelSystem(_name, _code) {}
 
void FeeManager::displayMenu() {
    cout << "\n=== Fee Manager ===" << endl;
    cout << "1. Generate Fee for Student" << endl;
    cout << "2. Mark Fee as Paid" << endl;
    cout << "3. Display All Fees" << endl;
    cout << "4. Display Pending Fees" << endl;
    cout << "5. Display Fees by Student" << endl;
    cout << "6. Calculate Total Due" << endl;
    cout << "7. Save to File" << endl;
    cout << "8. Load from File" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
}
 
void FeeManager::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); choice = -1; continue; }
        if (choice == 1) {
            String student_id, due_date;
            float amount;
            cout << "Enter Student ID: ";
            cin >> student_id;
            cout << "Enter Amount: ";
            cin >> amount;
            cout << "Enter Due Date: ";
            cin >> due_date;
            generateFeeForStudent(student_id, amount, due_date);
        } else if (choice == 2) {
            String student_id;
            cout << "Enter Student ID: ";
            cin >> student_id;
            markPaid(student_id);
        } else if (choice == 3) {
            displayAll();
        } else if (choice == 4) {
            displayPending();
        } else if (choice == 5) {
            String student_id;
            cout << "Enter Student ID: ";
            cin >> student_id;
            displayByStudent(student_id);
        } else if (choice == 6) {
            cout << "Total Due: " << calcTotalDue() << endl;
        } else if (choice == 7) {
            saveToFile();
        } else if (choice == 8) {
            loadFromFile();
        }
    } while (choice != 0);
}
 
void FeeManager::generateFees(Vector<Room*>& _rooms, Vector<String>& _allocated_to) {
    String due_date;
    cout << "Enter Due Date: ";
    cin >> due_date;
    int count = 0;
    for (int i = 0; i < _rooms.size(); i++) {
        if (!_allocated_to[i].empty()) {
            float amount = _rooms[i]->calcFee();
            int parts_count = 0;
            String* parts = _allocated_to[i].split(',', parts_count);
            for (int j = 0; j < parts_count; j++) {
                if (!parts[j].empty()) {
                    bool already_exists = false;
                    for (int k = 0; k < fees.size(); k++) {
                        if (fees[k].getStudentId() == parts[j] && !fees[k].isPaid()) {
                            already_exists = true;
                            break;
                        }
                    }
                    if (already_exists) {
                        cout << "Unpaid fee already exists for student " << parts[j] << ", skipping." << endl;
                        continue;
                    }
                    fees.push_back(Fee(parts[j], amount, due_date));
                    cout << "Fee " << amount << " generated for student " << parts[j]
                         << " (Room " << _rooms[i]->getRoomNo() << ")" << endl;
                    count++;
                }
            }
            delete[] parts;
        }
    }
    if (count == 0)
        cout << "No new fees generated." << endl;
    else
        cout << count << " fee(s) generated successfully." << endl;
}
 
void FeeManager::generateFeeForStudent(String _student_id, float _amount, String _due_date) {
    fees.push_back(Fee(_student_id, _amount, _due_date));
    cout << "Fee generated successfully." << endl;
}
 
void FeeManager::markPaid(String _student_id) {
    for (int i = 0; i < fees.size(); i++) {
        if (fees[i].getStudentId() == _student_id && !fees[i].isPaid()) {
            fees[i].markPaid();
            cout << "Fee marked as paid." << endl;
            return;
        }
    }
    cout << "No unpaid fee found for this student." << endl;
}
 
void FeeManager::displayPending() {
    bool found = false;
    for (int i = 0; i < fees.size(); i++) {
        if (!fees[i].isPaid()) {
            fees[i].display();
            cout << "---" << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No pending fees." << endl;
}
 
void FeeManager::displayAll() {
    if (fees.size() == 0) {
        cout << "No fees found." << endl;
        return;
    }
    for (int i = 0; i < fees.size(); i++) {
        fees[i].display();
        cout << "---" << endl;
    }
}
 
void FeeManager::displayByStudent(String _student_id) {
    bool found = false;
    for (int i = 0; i < fees.size(); i++) {
        if (fees[i].getStudentId() == _student_id) {
            fees[i].display();
            cout << "---" << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No fees found for this student." << endl;
}
 
float FeeManager::calcTotalDue() {
    float total = 0;
    for (int i = 0; i < fees.size(); i++) {
        if (!fees[i].isPaid())
            total += fees[i].getAmount();
    }
    return total;
}
 
void FeeManager::saveToFile() {
    ofstream file("fees.txt");
    for (int i = 0; i < fees.size(); i++) {
        file << fees[i].getStudentId() << "\t"
             << fees[i].getAmount() << "\t"
             << fees[i].getDueDate() << "\t"
             << (fees[i].isPaid() ? "1" : "0") << "\n";
    }
    file.close();
    cout << "Saved to file." << endl;
}
 
void FeeManager::loadFromFile() {
    ifstream file("fees.txt");
    if (!file.is_open()) {
        cout << "File not found." << endl;
        return;
    }
    fees.clear();
    String line;
    while (true) {
        line.getline(file, '\n');
        if (line.empty())
            break;
        int count = 0;
        String* parts = line.split('\t', count);
        if (count >= 4) {
            int len = parts[1].size();
            char* buf = new char[len + 1];
            for (int k = 0; k < len; k++) buf[k] = parts[1][k];
            buf[len] = '\0';
            float amount = (float)atof(buf);
            delete[] buf;
            Fee f(parts[0], amount, parts[2]);
            if (parts[3] == "1")
                f.markPaid();
            fees.push_back(f);
        }
        delete[] parts;
    }
    file.close();
    cout << "Loaded from file." << endl;
}

FeeManager::~FeeManager() {}