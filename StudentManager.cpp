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
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
}
 
void StudentManager::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); choice = -1; continue; }
        cin.ignore(10000, '\n');
        if (choice == 1) {
            addStudent();
        } else if (choice == 2) {
            String roll_no;
            cout << "Enter Roll No: ";
            cin >> roll_no;
            cin.ignore(10000, '\n');
            removeStudent(roll_no);
        } else if (choice == 3) {
            String roll_no;
            cout << "Enter Roll No: ";
            cin >> roll_no;
            cin.ignore(10000, '\n');
            Student* s = searchStudent(roll_no);
            if (s != nullptr)
                s->displayInfo();
            else
                cout << "Student not found." << endl;
        } else if (choice == 4) {
            String roll_no;
            cout << "Enter Roll No: ";
            cin >> roll_no;
            cin.ignore(10000, '\n');
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
    name.getline(cin, '\n');
    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(10000, '\n');
    cout << "Enter Phone: ";
    cin >> phone;
    cin.ignore(10000, '\n');
    cout << "Enter Roll No: ";
    cin >> roll_no;
    cin.ignore(10000, '\n');
    cout << "Enter Program: ";
    cin >> program;
    cin.ignore(10000, '\n');
    cout << "Enter Year: ";
    cin >> year;
    while (cin.fail() || year < 1) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "Invalid year. Enter a positive year: ";
        cin >> year;
    }
    cin.ignore(10000, '\n');
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
    cout << "\n--- Current Info ---" << endl;
    s->displayInfo();
    int choice;
    cout << "\n1. Update Name" << endl;
    cout << "2. Update Phone" << endl;
    cout << "3. Update Program" << endl;
    cout << "4. Update Year" << endl;
    cout << "0. Cancel" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1) {
        String name;
        cout << "Enter new Name: ";
        name.getline(cin, '\n');
        s->setName(name);
        cout << "Updated successfully." << endl;
    } else if (choice == 2) {
        String phone;
        cout << "Enter new Phone: ";
        cin >> phone;
        cin.ignore(10000, '\n');
        s->setPhone(phone);
        cout << "Updated successfully." << endl;
    } else if (choice == 3) {
        String program;
        cout << "Enter new Program: ";
        cin >> program;
        cin.ignore(10000, '\n');
        s->setProgram(program);
        cout << "Updated successfully." << endl;
    } else if (choice == 4) {
        int year;
        cout << "Enter new Year: ";
        cin >> year;
        while (cin.fail() || year < 1) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid year. Enter a positive year: ";
            cin >> year;
        }
        cin.ignore(10000, '\n');
        s->setYear(year);
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
        file << students[i]->getName() << "\t"
             << students[i]->getId() << "\t"
             << students[i]->getPhone() << "\t"
             << students[i]->getRollNo() << "\t"
             << students[i]->getProgram() << "\t"
             << students[i]->getYear() << "\t"
             << students[i]->getRoomNo() << "\n";
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
    String line;
    while (true) {
        line.getline(file, '\n');
        if (line.empty())
            break;
        int count = 0;
        String* parts = line.split('\t', count);
        if (count >= 7) {
            Student* s = new Student(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5].stoi());
            s->setRoomNo(parts[6]);
            students.push_back(s);
        }
        delete[] parts;
    }
    file.close();
    cout << "Loaded from file." << endl;
}
 
StudentManager::~StudentManager() {
    for (int i = 0; i < students.size(); i++)
        delete students[i];
}