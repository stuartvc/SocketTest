#ifndef USER_H_
#define USER_H_
#include <string>
#include <stdlib.h>

using namespace std;

class user {
    public:
        user();
        user(std::string name,
             std::string location,
             int age);
        ~user();

        std::string getName();
        std::string getLocation();
        int getAge();
        void setName(std::string newName);
        void setLocation(std::string newLocation);
        void setAge(int newAge);

    private:
        std::string name;
        std::string location;
        int age;
};



#endif
