#ifndef REQUEST_H_
#define REQUEST_H_
#include <string>
#include <map>
#include <iostream>
#include <stdio.h>

using namespace std;

enum Command {
    getCom = 0,
    setCom = 1,
    delCom = 2,
    noCom = 3
};


class Request {
    public:
        Request();
        Request(Command command, 
                 string name, 
                 string location, 
                 int age, 
                 int password);

        inline Command getCommand() {
            return command_;
        }

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

        inline void addQuery(map<string, string> query) {
            query_ = query;
            return;
        }

        string getQuery(string key);

        void setData();

    private:
        Command command_;
        string name_;
        string location_;
        int age_;
        int password_;
        map<string, string> query_;
};


#endif
