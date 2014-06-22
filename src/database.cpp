#include "database.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <openssl/md5.h>
#include "logging.h"
#include <stdio.h>


database::database(char* filename) {
    db = NULL;
    open(filename);
    vector<vector<string> > tableExist = query("SELECT name FROM sqlite_master WHERE type='table' AND name='USER';");
    if (tableExist.empty() || std::find(tableExist.at(0).begin(), tableExist.at(0).end(), "USER") == tableExist.at(0).end()){
        query("CREATE TABLE USER (name text NOT NULL, location text NOT NULL, age int NOT NULL)");
    }
    tableExist = query("SELECT name FROM sqlite_master WHERE type='table' AND name='ACTIVITY';");
    if (tableExist.empty() || std::find(tableExist.at(0).begin(), tableExist.at(0).end(), "ACTIVITY") == tableExist.at(0).end()){
        query("CREATE TABLE ACTIVITY (name text NOT NULL, tableName text NOT NULL)");
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

int database::modifyUser(user *user) {
    isAuth(*user);
    ostringstream sqlSS;
    sqlSS << "UPDATE USER SET location=\""
          << user->getLocation() << "\",age="
          << user->getAge() << " WHERE name=\""
          << user->getName() << "\";";
    query(sqlSS.str().c_str());
    return 0;
}

user *database::getUser(user requestUser, user *ResponseUser) {
    ostringstream sqlSS;
    sqlSS << "SELECT * FROM USER WHERE name=\""
          << requestUser.getName() << "\";";
    vector<vector<string> > buf = query(sqlSS.str().c_str());
    if (!buf.empty() && buf[0].size() >= 3) {
        ResponseUser->setName(buf[0][0]);
        ResponseUser->setLocation(buf[0][1]);
        ResponseUser->setAge(atoi(buf[0][2].c_str()));
    }
    else {
        throw string("user not found");
    }

    return (ResponseUser);
}

int database::deleteUser(user user) {
    isAuth(user);

    ostringstream sqlSS;
    sqlSS << "DELETE FROM USER WHERE name=\""
          << user.getName() << "\";";
    query(sqlSS.str().c_str());
    ostringstream sqlSS1;
    sqlSS1 << "DELETE FROM AUTH WHERE name=\""
          << user.getName() << "\";";
    query(sqlSS1.str().c_str());

    return 0;
}

void database::close() {
    sqlite3_close(db);
}
bool database::setPassword(user *user) {
    ostringstream sqlSS;
    unsigned char md5[16];
    memset(md5, '\0', 16);
    MD5((unsigned const char*)user->getPassword().c_str(), user->getPassword().length(), md5);
    sqlSS << "INSERT INTO AUTH (name, password) VALUES (\"" << user->getName() << "\",\"";
    for (int i = 0; i < 16; i++) {
        sqlSS << uppercase << hex << setw(2) << setfill('0') << (int)md5[i] << dec;
    }
    sqlSS << "\");";
    query(sqlSS.str().c_str());
    return true;
}

void database::isAuth(user user) {
    ostringstream sqlSS;
    ostringstream md5SS;
    unsigned char md5[16];
    memset(md5, '\0', 16);
    MD5((unsigned const char*)user.getPassword().c_str(), user.getPassword().length(), md5);
    for (int i = 0; i < 16; i++) {
        md5SS << uppercase << hex << setw(2) << setfill('0') << (int)md5[i] << dec;
    }
    sqlSS << "SELECT * FROM AUTH WHERE name=\""
          << user.getName() << "\";";
    vector<vector<string> > buf = query(sqlSS.str().c_str());

    if (buf.empty() || buf[0].empty()) {
        log.log("user not found");
        throw string("user not found");
    }
    else if(buf[0][1].compare(md5SS.str())) {
        log.log("not authorised");
        throw string("not authorised");
    }
    else {
        log.log("request is authorised");
    }
}

