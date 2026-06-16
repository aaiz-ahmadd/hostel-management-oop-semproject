#include "Person.h"
#include <iostream>
using namespace std;
 
Person::Person(String _name, String _id, String _phone) {
    name = _name;
    id = _id;
    phone = _phone;
}
 
String Person::getName() {
    return name;
}
 
String Person::getId() {
    return id;
}
 
String Person::getPhone() {
    return phone;
}
 
Person::~Person() {}