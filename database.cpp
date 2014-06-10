#include "database.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <openssl/sha.h>
#include "logging.h"


database::database(char* filename) {
    db = NULL;
    open(filename);
    vector<vector<string> > tableExist = query("SELECT name FROM sqlite_master WHERE type='table' AND name='USER';");
    if (std::find(tableExist.at(0).begin(), tableExist.at(0).end(), "USER") == tableExist.at(0).end()){
        query("CREATE TABLE USER (name text NOT NULL, location text NOT NULL, age int NOT NULL)");
    }
    if (std::find(tableExist.at(0).begin(), tableExist.at(0).end(), "AUTH") == tableExist.at(0).end()){
        query("CREATE TABLE AUTH (name text NOT NULL, password int NOT NULL)");
    }
}

database::~database() {
    close();
}

bool database::open(char* filename) {
    return (sqlite3_open(filename, &db) == SQLITE_OK);
}

vector<vector<string> > database::query(const char* query) {
    sqlite3_stmt *statement;
    vector<vector<string> > results;

    if(sqlite3_prepare_v2(db, query, -1, &statement, 0) == SQLITE_OK)
    {
        int cols = sqlite3_column_count(statement);
        int result = 0;
        while(true)
        {
            result = sqlite3_step(statement);
             
            if(result == SQLITE_ROW)
            {
                vector<string> values;
                for(int col = 0; col < cols; col++)
                {
                     values.push_back((char*)sqlite3_column_text(statement, col));
                }
                results.push_back(values);
            }
            else
            {
                break;  
            }
        }
        
        sqlite3_finalize(statement);
    }
     
    string error = sqlite3_errmsg(db);
    if(error != "not an error") ;//cout << query << " " << error << endl;
     
    return results;  
}

int database::insertUser(user *user) {
    ostringstream sqlSS;
    sqlSS << "INSERT INTO USER ( name, location, age ) VALUES ( \"";
    sqlSS << user->getName() << "\",\"" 
          << user->getLocation() << "\"," 
          << user->getAge() << ");";

    query(sqlSS.str().c_str());
    setPassword(user);
    
    return 0;

}

user *database::getUser(user requestUser, user *ResponseUser) {
    if (isAuth(requestUser)) {
        ostringstream sqlSS;
        sqlSS << "SELECT * FROM USER WHERE name=\""
              << requestUser.getName() << "\";";
        vector<vector<string> > buf = query(sqlSS.str().c_str());
        ResponseUser->setName(buf[0][0]);
        ResponseUser->setLocation(buf[0][1]);
        ResponseUser->setAge(atoi(buf[0][2].c_str()));
    }
    else {
        log.log("not authorised");
    }

    return (ResponseUser);
}

int database::deleteUser(user user) {
    if (isAuth(user)) {
        ostringstream sqlSS;
        sqlSS << "DELETE FROM USER WHERE name=\""
              << user.getName() << "\";";
        query(sqlSS.str().c_str());
    }
    else {
        log.log("not authorised");
    }
    return 0;
}

void database::close() {
    sqlite3_close(db);
}
bool database::setPassword(user *user) {
    ostringstream sqlSS;
    sqlSS << "INSERT INTO AUTH (name, password) VALUES (\"" << user->getName() << "\"," << user->getPassword() << ");";
    query(sqlSS.str().c_str());
    return true;
}

bool database::isAuth(user user) {
    ostringstream sqlSS;
    unsigned char auth[256];
    SHA_CTX context;
    SHA1_Init(&context);
    char temp[50];
    sprintf(temp, "%i", user.getPassword());
    SHA1_Update(&context, temp, 4);
    SHA1_Final(auth, &context);
    //cout << "sha1: \"" << auth << "\"" << endl;
    sqlSS << "SELECT * FROM AUTH WHERE name=\""
          << user.getName() << "\";";
    vector<vector<string> > buf = query(sqlSS.str().c_str());

    return (user.getPassword() == atoi(buf[0][1].c_str()));
}


