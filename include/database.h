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
        // The database that contains all the installed packages.
        sqlite3 *installedDb;
        // The database that contains all the packages that can be installed.
        sqlite3 *packageDb;
        // The list of packages available.
        static map<string, Package> packagesAvailable;
        // The list of all installed packages.
        static map<string, Package> installedPackages;
        // Location of the yoink database (database where all possible packages are)
        const char *YOINK_DB = "/etc/yoink/db/yoink.db";
        // Location of the installed package database
        const char *INSTALLED_DB = "/etc/yoink/db/installed.db";
        // The SQL to run when we are creating a database
        const char *CREATE_TABLE_SQL =
                "CREATE TABLE IF NOT EXISTS Packages("
                "Name           TEXT    NOT NULL UNIQUE, "
                "File           TEXT    NOT NULL UNIQUE, "
                "Dependency          TEXT     NOT NULL, "
                "Version            INT     NOT NULL,"
                "GUID TEXT NOT NULL UNIQUE); ";
        // The SQL to run when we are querying packages.
        const char *QUERY_PACKAGES_SQL = "SELECT * FROM Packages;";
        static vector<string> splitter(const string &line, char delimiter);
        static void addPackage(Package p, map<string, Package> &list);
        static int queryAvailablePackagesCallback([[maybe_unused]] void *data, [[maybe_unused]] int argc, char **argv,
                                                  [[maybe_unused]] char **azColName);
        static int queryPackagesInstalledCallback([[maybe_unused]] void *data, [[maybe_unused]] int argc, char **argv,
                                                  [[maybe_unused]] char **azColName);
        static int getPackagesFromDatabase(char *const *argv, map<string, Package> &list);
        sqlite3_stmt *stmt;
    public:
        Database();
        ~Database();
        static map<string, Package> getPackagesAvailable();
        static map<string, Package> getInstalledPackages();
        Package getPackageByName(string name);


        static int queryDatabase(char *const *argv, map<string, Package> &list);
};


#endif //YOINK_DATABASE_H
