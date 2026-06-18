#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H
 
#include "HostelSystem.h"
#include "Room.h"
#include "SingleRoom.h"
#include "SharedRoom.h"
#include "Student.h"
#include "Vector.h"
 
class RoomManager : public HostelSystem {
    Vector<Room*> rooms;
    Vector<String> allocated_to;
public:
    RoomManager(String _name, String _code);
    void run() override;
    void displayMenu() override;
    void addRoom();
    void allocateRoom(String _room_no, Student* _student);
    void deallocateRoom(String _room_no);
    void displayRooms();
    void displayAvailable();
    void displayOccupied();
    bool isAvailable(String _room_no);
    Room* getRoom(String _room_no);
    Vector<Room*>& getRooms();
    Vector<String>& getAllocatedTo();
    void saveToFile();
    void loadFromFile();
    ~RoomManager();
};
 
#endif