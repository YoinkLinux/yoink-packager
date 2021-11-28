//
// Created by gcpease on 11/25/2021.
//

#include <database.h>

/**
 * Initializes the yoink databases.
 */
Database::Database(const char *filePath) {
    database = nullptr;
    if (sqlite3_open(filePath, &database) == SQLITE_OK) {
        sqlite3_prepare(database, QUERY_PACKAGES_SQL, -1, &stmt, nullptr);
        sqlite3_step(stmt);
        while (sqlite3_column_text(stmt, 0)) {
            string name = string((char *) sqlite3_column_text(stmt, 0));
            string file = string((char *) sqlite3_column_text(stmt, 1));
            string depends = string((char *) sqlite3_column_text(stmt, 2));
            vector<string> dependencies = splitter(depends, ' ');
            int version = stoi(string((char *) sqlite3_column_text(stmt, 3)));
            string guid = string((char *) sqlite3_column_text(stmt, 4));
            Package p(name, file, dependencies, version, guid);
            addPackage(p);
            sqlite3_step(stmt);
        }
    }
}

/**
 * Pulls data from the database and inserts it to the list.
 * @param argv - Data from database.
 * @param list  - The list to insert to.
 * @return
 */
int Database::queryDatabase([[maybe_unused]] void *data, [[maybe_unused]] int argc, char **argv,
                            [[maybe_unused]] char **azColName) {
    string packageName = argv[0];
    string fileName = argv[1];
    std::vector<string> dependencies = splitter(argv[2], ' ');
    string version = argv[3];
    string guid = argv[4];
    Package p(packageName, fileName, dependencies, stoi(version), guid);
    addPackage(p);
    return 0;
}

/**
 * Destructors for Yoink databases.
 */
Database::~Database() {
    sqlite3_close(database);
}

/**
 * Gets all of the packages that are available for download.
 * @return
 */
map<string, Package> Database::getPackages() {
    return packages;
}

/**
 * Splits the given line based on the delimiter.
 * @param line - The line we want to split.
 * @param delimiter - The delimiter used to split the line.
 * @return A vector of strings split based off the delimiter.
 */
std::vector<string> Database::splitter(const string &line, char delimiter) {
    std::vector<string> result;
    std::stringstream ss(line);
    string item;
    while (getline(ss, item, delimiter))
        result.push_back(item);
    return result;
}

/**
 * Adds a package to the given list.
 * @param package - The package to add.
 * @param list - The list to add the package to.
 */
void Database::addPackage(Package package) {
    packages.insert(std::make_pair(package.getName(), package));
}

/**
 * Gets an installed package based off its name.
 * @param name - The name of the package.
 * @return The package that corresponds to that name. Will return an empty package if that name does not exist.
 */
Package Database::getPackageByName(const string &name) {
    if (packages.count(name))
        return packages[name];
    Package p;
    return p;
}

Database::Database() {
    database = nullptr;
}
