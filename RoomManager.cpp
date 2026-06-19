#include "RoomManager.h"
#include <iostream>
#include <fstream>
using namespace std;
 
RoomManager::RoomManager(String _name, String _code) : HostelSystem(_name, _code) {}
 
void RoomManager::displayMenu() {
    cout << "\n=== Room Manager ===" << endl;
    cout << "1. Add Room" << endl;
    cout << "2. Deallocate Room" << endl;
    cout << "3. Display All Rooms" << endl;
    cout << "4. Display Available Rooms" << endl;
    cout << "5. Display Occupied Rooms" << endl;
    cout << "6. Save to File" << endl;
    cout << "7. Load from File" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
}
 
void RoomManager::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); choice = -1; continue; }
        cin.ignore(10000, '\n');
        if (choice == 1) {
            addRoom();
        } else if (choice == 2) {
            String room_no;
            cout << "Enter Room No: ";
            cin >> room_no;
            cin.ignore(10000, '\n');
            deallocateRoom(room_no);
        } else if (choice == 3) {
            displayRooms();
        } else if (choice == 4) {
            displayAvailable();
        } else if (choice == 5) {
            displayOccupied();
        } else if (choice == 6) {
            saveToFile();
        } else if (choice == 7) {
            loadFromFile();
        }
    } while (choice != 0);
}
 
void RoomManager::addRoom() {
    int type;
    cout << "1. Single Room  2. Shared Room: ";
    cin >> type;
    String room_no;
    cout << "Enter Room No: ";
    cin >> room_no;
    if (type == 1) {
        float rate;
        cout << "Enter Monthly Rate: ";
        cin >> rate;
        while (cin.fail() || rate <= 0) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid rate. Enter a positive value: ";
            cin >> rate;
        }
        cin.ignore(10000, '\n');
        rooms.push_back(new SingleRoom(room_no, rate));
        allocated_to.push_back("");
    } else {
        int capacity;
        float total_rate;
        cout << "Enter Capacity (min 2): ";
        cin >> capacity;
        while (cin.fail() || capacity < 2) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid capacity. Enter 2 or more: ";
            cin >> capacity;
        }
        cin.ignore(10000, '\n');
        cout << "Enter Total Rate: ";
        cin >> total_rate;
        while (cin.fail() || total_rate <= 0) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid rate. Enter a positive value: ";
            cin >> total_rate;
        }
        cin.ignore(10000, '\n');
        rooms.push_back(new SharedRoom(room_no, capacity, total_rate));
        allocated_to.push_back("");
    }
    cout << "Room added successfully." << endl;
}
 
void RoomManager::allocateRoom(String _room_no, Student* _student) {
    Room* r = getRoom(_room_no);
    if (r == nullptr) {
        cout << "Room not found." << endl;
        return;
    }
    if (!_student->getRoomNo().empty()) {
        cout << "Student is already allocated to room " << _student->getRoomNo() << "." << endl;
        return;
    }
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getRoomNo() == _room_no) {
            int parts_count = 0;
            String* parts = allocated_to[i].split(',', parts_count);
            for (int j = 0; j < parts_count; j++) {
                if (parts[j] == _student->getRollNo()) {
                    delete[] parts;
                    cout << "Student is already allocated to this room." << endl;
                    return;
                }
            }
            delete[] parts;
            break;
        }
    }
    if (!isAvailable(_room_no)) {
        cout << "Room is not available." << endl;
        return;
    }
    if (r->getType() == "Shared") {
        SharedRoom* sr = (SharedRoom*)r;
        sr->addOccupant();
    } else {
        r->setOccupied(true);
    }
    _student->setRoomNo(_room_no);
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getRoomNo() == _room_no) {
            if (allocated_to[i].empty())
                allocated_to[i] = _student->getRollNo();
            else
                allocated_to[i] = allocated_to[i] + "," + _student->getRollNo();
            break;
        }
    }
    cout << "Room allocated successfully." << endl;
}
 
void RoomManager::deallocateRoom(String _room_no) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getRoomNo() == _room_no) {
            if (rooms[i]->getType() == "Shared") {
                SharedRoom* sr = (SharedRoom*)rooms[i];
                while (sr->getNumOccupants() > 0)
                    sr->removeOccupant();
            } else {
                rooms[i]->setOccupied(false);
            }
            allocated_to[i] = "";
            cout << "Room deallocated successfully." << endl;
            return;
        }
    }
    cout << "Room not found." << endl;
}
 
void RoomManager::displayRooms() {
    if (rooms.size() == 0) {
        cout << "No rooms found." << endl;
        return;
    }
    for (int i = 0; i < rooms.size(); i++) {
        cout << "\n--- Room " << i + 1 << " ---" << endl;
        rooms[i]->displayInfo();
        if (allocated_to[i] != "")
            cout << "Allocated To: " << allocated_to[i] << endl;
    }
}
 
void RoomManager::displayAvailable() {
    bool found = false;
    for (int i = 0; i < rooms.size(); i++) {
        if (!rooms[i]->isOccupied()) {
            cout << "\n--- Available Room ---" << endl;
            rooms[i]->displayInfo();
            found = true;
        }
    }
    if (!found)
        cout << "No available rooms." << endl;
}
 
void RoomManager::displayOccupied() {
    bool found = false;
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->isOccupied()) {
            cout << "\n--- Occupied Room ---" << endl;
            rooms[i]->displayInfo();
            cout << "Allocated To: " << allocated_to[i] << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No occupied rooms." << endl;
}
 
bool RoomManager::isAvailable(String _room_no) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getRoomNo() == _room_no)
            return !rooms[i]->isOccupied();
    }
    return false;
}
 
Room* RoomManager::getRoom(String _room_no) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getRoomNo() == _room_no)
            return rooms[i];
    }
    return nullptr;
}
 
Vector<Room*>& RoomManager::getRooms() {
    return rooms;
}
 
Vector<String>& RoomManager::getAllocatedTo() {
    return allocated_to;
}
 
void RoomManager::saveToFile() {
    ofstream file("rooms.txt");
    for (int i = 0; i < rooms.size(); i++) {
        int occupants = 0;
        float rate = 0;
        if (rooms[i]->getType() == "Single") {
            SingleRoom* sr = (SingleRoom*)rooms[i];
            rate = sr->getRate();
            if(rooms[i]->isOccupied())
                occupants = 1;
            else
                occupants = 0;
        } else {
            SharedRoom* sr = (SharedRoom*)rooms[i];
            rate = sr->getRate();
            occupants = sr->getNumOccupants();
        }
        file << rooms[i]->getType() << "\t"
             << rooms[i]->getRoomNo() << "\t"
             << rate << "\t"
             << rooms[i]->getCapacity() << "\t"
             << occupants << "\t"
             << allocated_to[i] << "\n";
    }
    file.close();
    cout << "Saved to file." << endl;
}

void RoomManager::loadFromFile() {
    ifstream file("rooms.txt");
    if (!file.is_open()) {
        cout << "File not found." << endl;
        return;
    }
    for (int i = 0; i < rooms.size(); i++)
        delete rooms[i];
    rooms.clear();
    allocated_to.clear();
    String line;
    while (true) {
        line.getline(file, '\n');
        if (line.empty()) break;
        int count = 0;
        String* parts = line.split('\t', count);
        if (count >= 6) {
            String type     = parts[0];
            String room_no  = parts[1];
            float  rate     = parts[2].stof();
            int    capacity = parts[3].stoi();
            int    occupants = parts[4].stoi();
            String alloc    = parts[5];
            if (type == "Single") {
                SingleRoom* sr = new SingleRoom(room_no, rate);
                if (occupants > 0) sr->setOccupied(true);
                rooms.push_back(sr);
            } else {
                SharedRoom* sr = new SharedRoom(room_no, capacity, rate);
                for (int j = 0; j < occupants; j++) sr->addOccupant();
                rooms.push_back(sr);
            }
            allocated_to.push_back(alloc);
        }
        delete[] parts;
    }
    file.close();
    cout << "Loaded from file." << endl;
}

RoomManager::~RoomManager() {
    for (int i = 0; i < rooms.size(); i++)
        delete rooms[i];
}