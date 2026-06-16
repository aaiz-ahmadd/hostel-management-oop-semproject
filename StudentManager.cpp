#include "StudentManager.h"
#include <iostream>
#include <fstream>
using namespace std;
 
StudentManager::StudentManager(String _name, String _code) : HostelSystem(_name, _code) {}
 
void StudentManager::displayMenu() {
    cout << "\n=== Student Manager ===" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Remove Student" << endl;
    cout << "3. Search Student" << endl;
    cout << "4. Update Student" << endl;
    cout << "5. Sort Students" << endl;
    cout << "6. Display All" << endl;
    cout << "7. Save to File" << endl;
    cout << "8. Load from File" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter choice: ";
}
 
void StudentManager::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        if (choice == 1) {
            addStudent();
        } else if (choice == 2) {
            String roll_no;
            cout << "Enter Roll No: ";
            cin >> roll_no;
            removeStudent(roll_no);
        } else if (choice == 3) {
            String roll_no;
            cout << "Enter Roll No: ";
            cin >> roll_no;
            Student* s = searchStudent(roll_no);
            if (s != nullptr)
                s->displayInfo();
            else
                cout << "Student not found." << endl;
        } else if (choice == 4) {
            String roll_no;
            cout << "Enter Roll No: ";
            cin >> roll_no;
            updateStudent(roll_no);
        } else if (choice == 5) {
            sortStudents();
        } else if (choice == 6) {
            displayAll();
        } else if (choice == 7) {
            saveToFile();
        } else if (choice == 8) {
            loadFromFile();
        }
    } while (choice != 0);
}
 
void StudentManager::addStudent() {
    String name, id, phone, roll_no, program;
    int year;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Phone: ";
    cin >> phone;
    cout << "Enter Roll No: ";
    cin >> roll_no;
    cout << "Enter Program: ";
    cin >> program;
    cout << "Enter Year: ";
    cin >> year;
    students.push_back(new Student(name, id, phone, roll_no, program, year));
    cout << "Student added successfully." << endl;
}
 
void StudentManager::removeStudent(String _roll_no) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i]->getRollNo() == _roll_no) {
            delete students[i];
            students.erase(i);
            cout << "Student removed successfully." << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}
 
Student* StudentManager::searchStudent(String _roll_no) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i]->getRollNo() == _roll_no)
            return students[i];
    }
    return nullptr;
}
 
void StudentManager::updateStudent(String _roll_no) {
    Student* s = searchStudent(_roll_no);
    if (s == nullptr) {
        cout << "Student not found." << endl;
        return;
    }
    int choice;
    cout << "1. Update Room No" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    if (choice == 1) {
        String room_no;
        cout << "Enter new Room No: ";
        cin >> room_no;
        s->setRoomNo(room_no);
        cout << "Updated successfully." << endl;
    }
}
 
void StudentManager::sortStudents() {
    for (int i = 0; i < students.size() - 1; i++) {
        for (int j = 0; j < students.size() - i - 1; j++) {
            if (students[j]->getRollNo() > students[j + 1]->getRollNo()) {
                Student* temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    cout << "Students sorted by roll number." << endl;
}
 
void StudentManager::displayAll() {
    if (students.size() == 0) {
        cout << "No students found." << endl;
        return;
    }
    for (int i = 0; i < students.size(); i++) {
        cout << "\n--- Student " << i + 1 << " ---" << endl;
        students[i]->displayInfo();
    }
}
 
void StudentManager::saveToFile() {
    ofstream file("students.txt");
    for (int i = 0; i < students.size(); i++) {
        file << students[i]->getName() << "\n";
        file << students[i]->getId() << "\n";
        file << students[i]->getPhone() << "\n";
        file << students[i]->getRollNo() << "\n";
        file << students[i]->getProgram() << "\n";
        file << students[i]->getYear() << "\n";
        file << students[i]->getRoomNo() << "\n";
    }
    file.close();
    cout << "Saved to file." << endl;
}
 
void StudentManager::loadFromFile() {
    ifstream file("students.txt");
    if (!file.is_open()) {
        cout << "File not found." << endl;
        return;
    }
    for (int i = 0; i < students.size(); i++)
        delete students[i];
    students.clear();
    String name, id, phone, roll_no, program, room_no, year_str;
    while (true) {
        name.getline(file, '\n');
        if (name.empty())
            break;
        id.getline(file, '\n');
        phone.getline(file, '\n');
        roll_no.getline(file, '\n');
        program.getline(file, '\n');
        year_str.getline(file, '\n');
        room_no.getline(file, '\n');
        Student* s = new Student(name, id, phone, roll_no, program, year_str.stoi());
        s->setRoomNo(room_no);
        students.push_back(s);
    }
    file.close();
    cout << "Loaded from file." << endl;
}
 
StudentManager::~StudentManager() {
    for (int i = 0; i < students.size(); i++)
        delete students[i];
}