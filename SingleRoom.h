#ifndef SINGLEROOM_H
#define SINGLEROOM_H
 
#include "Room.h"
 
class SingleRoom : public Room {
    float monthly_rate;
    String amenities;
public:
    SingleRoom(String _room_no, float _monthly_rate, String _amenities);
    float calcFee() override;
    String getType() override;
    void displayInfo() override;
    float getRate();
    ~SingleRoom();
};
 
#endif