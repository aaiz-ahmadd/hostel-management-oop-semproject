#ifndef ROOM_H
#define ROOM_H
 
#include "String.h"
 
class Room {
    String room_no;
    int capacity;
    bool occupied;
public:
    Room(String _room_no, int _capacity);
    virtual float calcFee() = 0;
    virtual String getType() = 0;
    virtual void displayInfo() = 0;
    String getRoomNo();
    int getCapacity();
    bool isOccupied();
    void setOccupied(bool _status);
    virtual ~Room();
};
 
#endif