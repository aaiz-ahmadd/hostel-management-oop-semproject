#ifndef MESSMANAGER_H
#define MESSMANAGER_H
 
#include "HostelSystem.h"
#include "MessMenu.h"
#include "Vector.h"
 
class MessManager : public HostelSystem {
    Vector<MessMenu> menus;
public:
    MessManager(String _name, String _code);
    void run() override;
    void displayMenu() override;
    void addMenu();
    void updateMenu(String _day, String _type, String _item);
    void displayWeeklyMenu();
    void saveToFile();
    void loadFromFile();
    ~MessManager();
};
 
#endif