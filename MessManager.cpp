#include "MessManager.h"
#include <iostream>
#include <fstream>
using namespace std;
 
MessManager::MessManager(String _name, String _code) : HostelSystem(_name, _code) {}
 
void MessManager::displayMenu() {
    cout << "\n=== Mess Manager ===" << endl;
    cout << "1. Add Menu" << endl;
    cout << "2. Update Menu" << endl;
    cout << "3. Display Weekly Menu" << endl;
    cout << "4. Save to File" << endl;
    cout << "5. Load from File" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
}
 
void MessManager::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); choice = -1; continue; }
        cin.ignore(10000, '\n');
        if (choice == 1) {
            addMenu();
        } else if (choice == 2) {
            String day, type, item;
            cout << "Enter Day: ";
            cin >> day;
            cin.ignore(10000, '\n');
            cout << "Enter Type (breakfast/lunch/dinner): ";
            cin >> type;
            cin.ignore(10000, '\n');
            cout << "Enter Item: ";
            item.getline(cin, '\n');
            updateMenu(day, type, item);
        } else if (choice == 3) {
            displayWeeklyMenu();
        } else if (choice == 4) {
            saveToFile();
        } else if (choice == 5) {
            loadFromFile();
        }
    } while (choice != 0);
}
 
void MessManager::addMenu() {
    String day;
    cout << "Enter Day: ";
    cin >> day;
    menus.push_back(MessMenu(day));
    cout << "Menu added for " << day << "." << endl;
}
 
void MessManager::updateMenu(String _day, String _type, String _item) {
    for (int i = 0; i < menus.size(); i++) {
        if (menus[i].getDay() == _day) {
            menus[i].setMeal(_type, _item);
            cout << "Menu updated." << endl;
            return;
        }
    }
    cout << "Day not found." << endl;
}
 
void MessManager::displayWeeklyMenu() {
    if (menus.size() == 0) {
        cout << "No menus found." << endl;
        return;
    }
    for (int i = 0; i < menus.size(); i++) {
        cout << "\n";
        menus[i].display();
    }
}
 
void MessManager::saveToFile() {
    ofstream file("menus.txt");
    for (int i = 0; i < menus.size(); i++) {
        file << menus[i].getDay() << "\t"
             << menus[i].getMeal("breakfast") << "\t"
             << menus[i].getMeal("lunch") << "\t"
             << menus[i].getMeal("dinner") << "\n";
    }
    file.close();
    cout << "Saved to file." << endl;
}
 
void MessManager::loadFromFile() {
    ifstream file("menus.txt");
    if (!file.is_open()) {
        cout << "File not found." << endl;
        return;
    }
    menus.clear();
    String line;
    while (true) {
        line.getline(file, '\n');
        if (line.empty())
            break;
        int count = 0;
        String* parts = line.split('\t', count);
        if (count >= 4) {
            MessMenu m(parts[0]);
            m.setMeal("breakfast", parts[1]);
            m.setMeal("lunch", parts[2]);
            m.setMeal("dinner", parts[3]);
            menus.push_back(m);
        }
        delete[] parts;
    }
    file.close();
    cout << "Loaded from file." << endl;
}
 
MessManager::~MessManager() {}