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

        inline int getPassword() {
            return password_;
        }

        inline int getSuccess() {
            return success_;
        }

        void set(user &User);

        void success(bool success) {
            success_ = success;
        }

    private:
        string name_;
        string location_;
        int age_;
        int password_;
        bool success_;
};

#endif
