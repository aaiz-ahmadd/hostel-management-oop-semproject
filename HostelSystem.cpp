#include "HostelSystem.h"
#include <iostream>
using namespace std;
 
HostelSystem::HostelSystem(String name, String code) {
    system_name = name;
    manager_code = code;
}
 
String HostelSystem::getSystemName() {
    return system_name;
}
 
bool HostelSystem::verifyCode(String code) {
    return manager_code == code;
}
 
HostelSystem::~HostelSystem() {}