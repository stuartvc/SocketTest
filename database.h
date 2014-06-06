#ifndef DATEBASE_H_
#define DATABASE_H_
#include "user.h"
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <vector>

using namespace std;

class database {
    public:
        database(char* filename);
        ~database();

        bool open(char* filename);
        vector<vector<string> >query(const char* query);
        int insertUser(user *user);
        user *getUser(char* name, user *user);
        void close();

    private:
        sqlite3 *db;
};



#endif
