#include "user.h"


user::user() {
    name_="";
    location_="";
    age_=0;
    password_=0;
}
user::user(std::string name,
           std::string location,
           int age,
           int password){
    name_ = name;
    location_ = location;
    age_ = age;
    password_ = password;
}
user::~user() {
}

std::string user::getName() {
    return name_;
}
std::string user::getLocation() {
    return location_;
}
int user::getAge() {
    return age_;
}
int user::getPassword() {
    return password_;
}
void user::setName(std::string name) {
    name_ = name;
}
void user::setLocation(std::string location) {
    location_ = location;
}
void user::setAge(int age) {
    age_ = age;
}
void user::setPassword(int password) {
    password_ = password;
}
