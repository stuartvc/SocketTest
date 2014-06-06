#ifndef HANDLER_H_
#define HANDLER_H_
#include "request.h"
#include "response.h"

class Handler {
    public:
        Handler();
        bool handleRequest(Request &request, Response &response);


    private:

};



#endif
