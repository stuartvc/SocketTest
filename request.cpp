#include "request.h"

Request::Request() {
    command_ = get;
    name_ = "";
    location_ = "";
    age_ = 0;
    password_ = 0;
}
Request::Request(Command command, 
                 string name, 
                 string location, 
                 int age, 
                 int password) {
    command_ = command;
    name_ = name;
    location_ = location;
    age_ = age;
    password_ = password;
}

string Request::getQuery(string key) {
    string value;
    try {
        value = query_.at(key);
    }
    catch (const exception &ex) {
        value = "error";
    }
    return value;
}
