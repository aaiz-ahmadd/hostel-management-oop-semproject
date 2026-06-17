#include "RoomManager.h"
#include <iostream>
using namespace std;
 
RoomManager::RoomManager(String _name, String _code) : HostelSystem(_name, _code) {}
 
void RoomManager::displayMenu() {
    cout << "=== Room Manager ===" << endl;
    cout << "1. Add Room" << endl;
    cout << "2. Deallocate Room" << endl;
    cout << "3. Display All Rooms" << endl;
    cout << "4. Display Available Rooms" << endl;
    cout << "5. Display Occupied Rooms" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
}
 
void RoomManager::run() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        if (choice == 1) {
            addRoom();
        } else if (choice == 2) {
            String room_no;
            cout << "Enter Room No: ";
            cin >> room_no;
            deallocateRoom(room_no);
        } else if (choice == 3) {
            displayRooms();
        } else if (choice == 4) {
            displayAvailable();
        } else if (choice == 5) {
            displayOccupied();
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
        String amenities;
        cout << "Enter Monthly Rate: ";
        cin >> rate;
        cout << "Enter Amenities: ";
        cin >> amenities;
        rooms.push_back(new SingleRoom(room_no, rate, amenities));
        allocated_to.push_back("");
    } else {
        int capacity;
        float total_rate;
        cout << "Enter Capacity: ";
        cin >> capacity;
        cout << "Enter Total Rate: ";
        cin >> total_rate;
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
    if (!isAvailable(_room_no)) {
        cout << "Room is not available." << endl;
        return;
    }
    r->setOccupied(true);
    _student->setRoomNo(_room_no);
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getRoomNo() == _room_no) {
            allocated_to[i] = _student->getRollNo();
            break;
        }
    }
    cout << "Room allocated successfully." << endl;
}
 
void RoomManager::deallocateRoom(String _room_no) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getRoomNo() == _room_no) {
            rooms[i]->setOccupied(false);
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
 
RoomManager::~RoomManager() {
    for (int i = 0; i < rooms.size(); i++)
        delete rooms[i];
}