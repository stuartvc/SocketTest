#include "response.h"

Response::Response() {
    name_ = "";
    location_ = "";
    age_ = 0;
    password_ = "";
}
Response::Response(string name, 
                   string location, 
                   int age, 
                   string password) {
    name_ = name;
    location_ = location;
    age_ = age;
    password_ = password;
}

void Response::set(user &User) {
    name_ = User.getName();
    location_ = User.getLocation();
    age_ = User.getAge();
    password_ = User.getPassword();
}
