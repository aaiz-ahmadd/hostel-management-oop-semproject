#include "Room.h"
#include <iostream>
using namespace std;
 
Room::Room(String _room_no, int _capacity) {
    room_no = _room_no;
    capacity = _capacity;
    occupied = false;
}
 
String Room::getRoomNo() {
    return room_no;
}
 
int Room::getCapacity() {
    return capacity;
}
 
bool Room::isOccupied() {
    return occupied;
}
 
void Room::setOccupied(bool _status) {
    occupied = _status;
}
 
Room::~Room() {}