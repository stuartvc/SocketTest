#include "handler.h"
#include <iostream>
#include <stdio.h>
#include "logging.h"



Handler::Handler() {
}

bool Handler::handleRequest(Request &request, Response &response, database &db) {
    if (getCom == request.getCommand()) {
        return handleGet(request, response, db);
    }
    else if (setCom == request.getCommand()) {
        return handleSet(request, response, db);
    }
    else if (modCom == request.getCommand()) {
        return handleMod(request, response, db);
    }
    else if (delCom == request.getCommand()) {
        return handleDel(request, response, db);
    }
    else {
        log.log("unknown command");
        return false;
    }
    //to stuff
    return true;
}

bool Handler::handleGet(Request &request, Response &response, database &db) {
    
    user requestUser;
    user responseUser;
    request.push(requestUser);

    db.getUser(requestUser, &responseUser);

    response.setSuccess(true);
    response.set(responseUser);

    log.log("Get complete");

    return true;
}

bool Handler::handleSet(Request &request, Response &response, database &db) {

    user requestUser;
    user responseUser;
    request.push(requestUser);

    try {
        db.getUser(requestUser, &responseUser);
    }
    catch (const string ex) {
        if (ex.compare("user not found"));
    }

    if (!responseUser.getName().empty()) {
        log.log("User already exists");
        throw string("User already exists");
    }

    db.insertUser(&requestUser);

    response.setSuccess(true);
    response.set(requestUser);
    log.log("Set complete");

    return true;
}
bool Handler::handleMod(Request &request, Response &response, database &db) {
    user User;
    request.push(User);
    db.modifyUser(&User);

    response.setSuccess(true);
    response.set(User);
    log.log("Mod complete");

    return true;

}

bool Handler::handleDel(Request &request, Response &response, database &db) {
    user responseUser;
    user requestUser;
    request.push(requestUser);

    db.getUser(requestUser, &responseUser);
    db.deleteUser(requestUser);
    response.setSuccess(true);
    response.set(responseUser);
    log.log("Del complete");
    return true;
}

