#include "handler.h"
#include <iostream>
#include <stdio.h>



Handler::Handler() {
}

bool Handler::handleRequest(Request &request, Response &response, database &db) {
    if (getCom == request.getCommand()) {
        return handleGet(request, response, db);
    }
    else if (setCom == request.getCommand()) {
        return handleSet(request, response, db);
    }
    else if (delCom == request.getCommand()) {
        return handleDel(request, response, db);
    }
    else {
        return false;
    }
    //to stuff
    return true;
}

bool Handler::handleGet(Request &request, Response &response, database &db) {
    
    user User;

    db.getUser((char*)request.getName().c_str(), &User);

    response.set(User);

    /*
    cout << "name is \"" << response.getName() << "\"\n"
         << "location is \"" << response.getLocation() << "\"\n"
         << "Age is \"" << response.getAge() << "\"\n"
         << "password is \"" << response.getPass() << "\"\n";*/
    return true;
}

bool Handler::handleSet(Request &request, Response &response, database &db) {
    return true;
}

bool Handler::handleDel(Request &request, Response &response, database &db) {
    return true;
}

