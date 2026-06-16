#ifndef HOSTELSYSTEM_H
#define HOSTELSYSTEM_H
 
#include "String.h"
 
class HostelSystem {
    String system_name;
    String manager_code;
public:
    HostelSystem(String name, String code);
    virtual void run() = 0;
    virtual void displayMenu() = 0;
    String getSystemName();
    bool verifyCode(String code);
    virtual ~HostelSystem();
};
 
#endif