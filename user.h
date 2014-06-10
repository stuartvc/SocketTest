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
             int age,
             int password);
        ~user();

        std::string getName();
        std::string getLocation();
        int getAge();
        int getPassword();
        void setName(std::string name);
        void setLocation(std::string location);
        void setAge(int age);
        void setPassword(int password);

    private:
        std::string name_;
        std::string location_;
        int age_;
        int password_;
};



#endif
