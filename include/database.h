//
// Created by gcpease on 11/25/2021.
//

#ifndef YOINK_DATABASE_H
#define YOINK_DATABASE_H

#include <sqlite3.h>
#include <package.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using std::map;
using std::string;
using std::vector;

class Database {
    private:
        // The database that contains all the packages that can be installed.
        sqlite3 *database;
        // The list of all installed packages.
        map<string, Package> packages;
        // Location of the yoink database (database where all possible packages are)
        const char *CREATE_TABLE_SQL =
                "CREATE TABLE IF NOT EXISTS Packages("
                "Name           TEXT    NOT NULL UNIQUE, "
                "File           TEXT    NOT NULL UNIQUE, "
                "Dependency          TEXT     NOT NULL, "
                "Version            INT     NOT NULL,"
                "GUID TEXT NOT NULL UNIQUE); ";
        // The SQL to run when we are querying packages.
        const char *QUERY_PACKAGES_SQL = "SELECT * FROM Packages;";
        // Unneeded but need this for SQL queries to work.
        sqlite3_stmt *stmt;
        static vector<string> splitter(const string &line, char delimiter);
        void addPackage(Package p);
        int queryDatabase([[maybe_unused]] void *data, [[maybe_unused]] int argc, char **argv,
                                 [[maybe_unused]] char **azColName);
    public:
        Database();
        explicit Database(const char* filePath);
        ~Database();
        map<string, Package> getPackages();
        Package getPackageByName(const string& name);
};


#endif //YOINK_DATABASE_H
