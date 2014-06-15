#include "database.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <openssl/md5.h>
#include "logging.h"


database::database(char* filename) {
    db = NULL;
    open(filename);
    vector<vector<string> > tableExist = query("SELECT name FROM sqlite_master WHERE type='table' AND name='USER';");
    if (tableExist.empty() || std::find(tableExist.at(0).begin(), tableExist.at(0).end(), "USER") == tableExist.at(0).end()){
        query("CREATE TABLE USER (name text NOT NULL, location text NOT NULL, age int NOT NULL)");
    }
    tableExist = query("SELECT name FROM sqlite_master WHERE type='table' AND name='AUTH';");
    if (tableExist.empty() || std::find(tableExist.at(0).begin(), tableExist.at(0).end(), "AUTH") == tableExist.at(0).end()){
        query("CREATE TABLE AUTH (name text NOT NULL, password text NOT NULL)");
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
    if(error != "not an error") log.log(string(query) + " " + error);
     
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
        if (!buf.empty() && buf[0].size() >= 3) {
            ResponseUser->setName(buf[0][0]);
            ResponseUser->setLocation(buf[0][1]);
            ResponseUser->setAge(atoi(buf[0][2].c_str()));
        }
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
        ostringstream sqlSS1;
        sqlSS1 << "DELETE FROM AUTH WHERE name=\""
              << user.getName() << "\";";
        query(sqlSS1.str().c_str());
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
    unsigned char md5[17];
    memset(md5, '\0', 17);
    MD5((unsigned const char*)user->getPassword().c_str(), user->getPassword().length(), md5);
    sqlSS << "INSERT INTO AUTH (name, password) VALUES (\"" << user->getName() << "\",\"" << md5 << "\");";
    query(sqlSS.str().c_str());
    return true;
}

bool database::isAuth(user user) {
    ostringstream sqlSS;
    unsigned char md5[17];
    memset(md5, '\0', 17);
    MD5((unsigned const char*)user.getPassword().c_str(), user.getPassword().length(), md5);
    sqlSS << "SELECT * FROM AUTH WHERE name=\""
          << user.getName() << "\";";
    vector<vector<string> > buf = query(sqlSS.str().c_str());

    return !(buf.empty() || buf[0].empty() || (buf[0][1].compare((const char*)md5)));
}

