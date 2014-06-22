#ifndef HANDLER_H_
#define HANDLER_H_
#include "request.h"
#include "response.h"
#include "database.h"

class Handler {
    public:
        Handler();
        bool handleRequest(Request &request, Response &response, database &db);

    private:

        bool handleGet(Request &request, Response &response, database &db);
        bool handleSet(Request &request, Response &response, database &db);
        bool handleMod(Request &request, Response &response, database &db);
        bool handleDel(Request &request, Response &response, database &db);

};

#endif
