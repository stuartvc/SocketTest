#include "response.h"

Response::Response() {
    name_ = "";
    location_ = "";
    age_ = 0;
    password_ = 0;
}
Response::Response(string name, 
                   string location, 
                   int age, 
                   int password) {
    name_ = name;
    location_ = location;
    age_ = age;
    password_ = password;
}
