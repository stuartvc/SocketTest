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
                 string password);

        inline string getName() {
            return name_;
        }

        inline string getLocation() {
            return location_;
        }

        inline int getAge() {
            return age_;
        }

        inline string getPassword() {
            return password_;
        }

        inline int getSuccess() {
            return success_;
        }

        inline string getMessage() {
            return message_;
        }

        void set(user &User);

        void setName(string name) {
            name_ = name;
        }

        void setSuccess(bool success) {
            success_ = success;
        }

        void setMessage(string message) {
            message_ = message;
        }

    private:
        string name_;
        string location_;
        int age_;
        string password_;
        bool success_;
        string message_;
};

#endif
