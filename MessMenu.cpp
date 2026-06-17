#include "MessMenu.h"
#include <iostream>
using namespace std;
 
MessMenu::MessMenu() {
    day = "";
    breakfast = "Not set";
    lunch = "Not set";
    dinner = "Not set";
}
 
MessMenu::MessMenu(String _day) {
    day = _day;
    breakfast = "Not set";
    lunch = "Not set";
    dinner = "Not set";
}
 
void MessMenu::setMeal(String _type, String _item) {
    if (_type == "breakfast")
        breakfast = _item;
    else if (_type == "lunch")
        lunch = _item;
    else if (_type == "dinner")
        dinner = _item;
}
 
String MessMenu::getMeal(String _type) {
    if (_type == "breakfast")
        return breakfast;
    if (_type == "lunch")
        return lunch;
    if (_type == "dinner")
        return dinner;
    return "Not found";
}
 
String MessMenu::getDay() {
    return day;
}
 
void MessMenu::display() {
    cout << "Day: " << day << endl;
    cout << "Breakfast: " << breakfast << endl;
    cout << "Lunch: " << lunch << endl;
    cout << "Dinner: " << dinner << endl;
}