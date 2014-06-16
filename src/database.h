#ifndef DATABASE_H_
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
        int modifyUser(user *user);
        user *getUser(user , user *ResponseUser);
        int deleteUser(user user);
        void close();

    private:
        bool setPassword(user *user);
        bool isAuth(user user);
        sqlite3 *db;
};



#endif
