#ifndef RESPONSE_H_
#define RESPONSE_H_
#include <string>
#include "user.h"

using namespace std;

class Response {
    public:
        Response();
        Response(string name, 
                 string location, 
                 int age, 
                 int password);

        inline string getName() {
            return name_;
        }

        inline string getLocation() {
            return location_;
        }

        inline int getAge() {
            return age_;
        }

        inline int getPass() {
            return password_;
        }

        void set(user &User);

    private:
        string name_;
        string location_;
        int age_;
        int password_;
};

#endif
