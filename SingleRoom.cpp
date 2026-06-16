#include "SingleRoom.h"
#include <iostream>
using namespace std;
 
SingleRoom::SingleRoom(String _room_no, float _monthly_rate, String _amenities) : Room(_room_no, 1) {
    monthly_rate = _monthly_rate;
    amenities = _amenities;
}
 
float SingleRoom::calcFee() {
    return monthly_rate;
}
 
String SingleRoom::getType() {
    return "Single";
}
 
void SingleRoom::displayInfo() {
    cout << "Room No: " << getRoomNo() << endl;
    cout << "Type: Single" << endl;
    cout << "Monthly Rate: " << monthly_rate << endl;
    cout << "Amenities: " << amenities << endl;
    if (isOccupied())
        cout << "Occupied: Yes" << endl;
    else
        cout << "Occupied: No" << endl;
}
 
float SingleRoom::getRate() {
    return monthly_rate;
}
 
SingleRoom::~SingleRoom() {}