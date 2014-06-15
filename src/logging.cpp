#include "logging.h"
#include <iostream>
#include <time.h>

logger log(MY_LOG_FILE);

logger::logger(std::string file) {
    logfile_.open(file.c_str(), std::ofstream::app);
}
logger::~logger() {
    logfile_.close();
}
void logger::log(std::string output) {
    time_t unixTime;
    time(&unixTime);
    char* time = ctime(&unixTime);
    time[24] = '\0';
    logfile_ << time << "\t" << output << "\n";
    logfile_.flush();
}


