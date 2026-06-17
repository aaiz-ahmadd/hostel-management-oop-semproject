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
 
void Person::setName(String _name) { name = _name; }
void Person::setPhone(String _phone) { phone = _phone; }

Person::~Person() {}