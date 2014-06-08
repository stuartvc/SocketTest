#ifndef LOGGING_H_
#define LOGGING_H_
#include <fstream>
#include <iostream>

#define MY_LOG_FILE "server.log"

class logger {
    public:
        logger(std::string);
        ~logger();
        void log(std::string output);

    private:
        std::ofstream logfile_;
};

//static logger log("log");
extern logger log;

#endif
