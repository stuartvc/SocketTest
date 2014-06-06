#include "user.h"


user::user() {
    name="";
    location="";
    age=0;
}
user::user(std::string newName,
           std::string newLocation,
           int newAge){
    name = newName;
    location = newLocation;
    age = newAge;
}
user::~user() {
}

std::string user::getName() {
    return name;
}
std::string user::getLocation() {
    return location;
}
int user::getAge() {
    return age;
}
void user::setName(std::string newName) {
    name = newName;
}
void user::setLocation(std::string newLocation) {
    location = newLocation;
}
void user::setAge(int newAge) {
    age = newAge;
}
