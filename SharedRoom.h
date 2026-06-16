#ifndef SHAREDROOM_H
#define SHAREDROOM_H
 
#include "Room.h"
 
class SharedRoom : public Room {
    float total_rate;
    int num_occupants;
public:
    SharedRoom(String _room_no, int _capacity, float _total_rate);
    float calcFee() override;
    String getType() override;
    void displayInfo() override;
    void addOccupant();
    void removeOccupant();
    float getRate();
    int getNumOccupants();
    ~SharedRoom();
};
 
#endif