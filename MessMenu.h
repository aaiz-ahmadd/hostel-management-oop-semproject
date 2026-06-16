#ifndef MESSMENU_H
#define MESSMENU_H
 
#include "String.h"
 
class MessMenu {
    String day;
    String breakfast;
    String lunch;
    String dinner;
public:
    MessMenu(String _day);
    void setMeal(String _type, String _item);
    String getMeal(String _type);
    String getDay();
    void display();
};

#endif