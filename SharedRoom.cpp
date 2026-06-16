#include "SharedRoom.h"
#include <iostream>
using namespace std;
 
SharedRoom::SharedRoom(String _room_no, int _capacity, float _total_rate) : Room(_room_no, _capacity) {
    total_rate = _total_rate;
    num_occupants = 0;
}
 
float SharedRoom::calcFee() {
    if (num_occupants == 0)
        return total_rate;
    return total_rate / num_occupants;
}
 
String SharedRoom::getType() {
    return "Shared";
}
 
void SharedRoom::displayInfo() {
    cout << "Room No: " << getRoomNo() << endl;
    cout << "Type: Shared" << endl;
    cout << "Total Rate: " << total_rate << endl;
    cout << "Capacity: " << getCapacity() << endl;
    cout << "Occupants: " << num_occupants << endl;
    cout << "Fee Per Person: " << calcFee() << endl;
    if (isOccupied())
        cout << "Occupied: Yes" << endl;
    else
        cout << "Occupied: No" << endl;
}
 
void SharedRoom::addOccupant() {
    if (num_occupants < getCapacity()) {
        num_occupants++;
        if (num_occupants == getCapacity())
            setOccupied(true);
    }
}
 
void SharedRoom::removeOccupant() {
    if (num_occupants > 0) {
        num_occupants--;
        if (num_occupants == 0)
            setOccupied(false);
    }
}
 
float SharedRoom::getRate() {
    return total_rate;
}
 
int SharedRoom::getNumOccupants() {
    return num_occupants;
}
 
SharedRoom::~SharedRoom() {}