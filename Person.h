#ifndef PERSON_H
#define PERSON_H
 
#include "String.h"
 
class Person {
    String name;
    String id;
    String phone;
public:
    Person(String _name, String _id, String _phone);
    virtual void displayInfo() = 0;
    String getName();
    String getId();
    String getPhone();
    void setName(String _name);
    void setPhone(String _phone);
    virtual ~Person();
};
 
#endif