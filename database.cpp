#include "database.h"
#include <sstream>




database::database(char* filename) {
    db = NULL;
    open(filename);
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
    
    return 0;

}

user *database::getUser(char* name, user *user) {
    ostringstream sqlSS;
    sqlSS << "SELECT * FROM USER WHERE name=\""
          << name << "\";";
    vector<vector<string> > buf = query(sqlSS.str().c_str());
    user->setName(buf[0][0]);
    user->setLocation(buf[0][1]);
    user->setAge(atoi(buf[0][2].c_str()));

    return (user);
}

void database::close() {
    sqlite3_close(db);
}

