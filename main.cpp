#include "database.h"
#include "user.h"
#include "parse.h"
#include "request.h"
#include "response.h"
#include "handler.h"
#include "socket.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void run(database &db);

int main() {
    database db((char*)"test.db");

    //user newUser1("Stuart", "Toronto", 22);
    //db.insertUser(&newUser1);

    user User;

    vector<vector<std::string> > vec = db.query((const char*)"SELECT * FROM USER");
    for( std::vector<vector<std::string> >::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        vector<std::string> temp = *i;
        for ( std::vector<std::string>::const_iterator j = temp.begin(); j != temp.end(); j++)
            std::cout << *j << ' ';
        cout << endl;
    }

    db.getUser((char*)"stuart", &User);
    cout << User.getName() << ", "
         << User.getLocation() << ", "
         << User.getAge() << endl;

    //user newUser("Jim", "Victoria", 22);

    //db.insertUser(&newUser);

    run(db);
    db.close();

    return 0;
}

void run(database &db) {
    Socket socket;
    Handler handler;
    Response response;
    Request request;
    while (1) {
        socket.readRequest(request);
        handler.handleRequest(request, response, db);
        socket.writeResponse(response);
    }
    return ; 
}
