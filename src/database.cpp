//
// Created by gcpease on 11/25/2021.
//

#include <database.h>

map<string, Package> Database::packagesAvailable;
map<string, Package> Database::installedPackages;

/**
 * Initializes the yoink databases.
 */
Database::Database() {
    installedDb = nullptr;
    packageDb = nullptr;
    if (sqlite3_open(YOINK_DB, &packageDb) == SQLITE_OK) {
        sqlite3_prepare(packageDb, QUERY_PACKAGES_SQL, -1, &stmt, nullptr);
        sqlite3_exec(packageDb, QUERY_PACKAGES_SQL, queryAvailablePackagesCallback, nullptr, nullptr);
    }
    if (sqlite3_open(INSTALLED_DB, &installedDb) == SQLITE_OK) {
        sqlite3_prepare(installedDb, QUERY_PACKAGES_SQL, -1, &stmt, nullptr);
        sqlite3_exec(installedDb, QUERY_PACKAGES_SQL, queryPackagesInstalledCallback, nullptr, nullptr);
    }
}

/**
 * Gets all the packages available to install
 * @param data
 * @param argc
 * @param argv
 * @param azColName
 * @return
 */
int Database::queryAvailablePackagesCallback([[maybe_unused]] void *data, [[maybe_unused]] int argc, char **argv,
                                             [[maybe_unused]] char **azColName) {
    return queryDatabase(argv, packagesAvailable);
}

/**
 * Gets all the packages that already have been installed.
 * @param data
 * @param argc
 * @param argv
 * @param azColName
 * @return
 */
int Database::queryPackagesInstalledCallback([[maybe_unused]] void *data, [[maybe_unused]] int argc, char **argv,
                                             [[maybe_unused]] char **azColName) {
    return queryDatabase(argv, installedPackages);
}

/**
 * Pulls data from the database and inserts it to the list.
 * @param argv - Data from database.
 * @param list  - The list to insert to.
 * @return
 */
int Database::queryDatabase(char *const *argv, map<string, Package> &list) {
    string packageName = argv[0];
    string fileName = argv[1];
    std::vector<string> dependencies = splitter(argv[2], ' ');
    string version = argv[3];
    string guid = argv[4];
    Package p(packageName, fileName, dependencies, stoi(version), guid);
    addPackage(p, list);
    return 0;
}

/**
 * Gets a package from the database
 * @param argv - The data from the database
 * @param list - The list to add to.
 * @return
 */
int Database::getPackagesFromDatabase(char *const *argv, map<string, Package> &list) {
    string packageName = argv[0];
    string fileName = argv[1];
    vector<string> dependencies = splitter(argv[2], ' ');
    string version = argv[3];
    string guid = argv[4];
    Package p(packageName, fileName, dependencies, stoi(version), guid);
    addPackage(p, list);
    return 0;
}

/**
 * Destructors for Yoink databases.
 */
Database::~Database() {
    sqlite3_close(installedDb);
    sqlite3_close(packageDb);
}

/**
 * Gets all of the packages that are available for download.
 * @return
 */
map<string, Package> Database::getPackagesAvailable() {
    return packagesAvailable;
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
void Database::addPackage(Package package, map<string, Package> &list) {
    list.insert(std::make_pair(package.getName(), package));
}

/**
 * Gets all of the installed packages.
 * @return A map of all of the installed packages, queryable by name.
 */
map<string, Package> Database::getInstalledPackages() {
    return installedPackages;
}

/**
 * Gets an installed package based off its name.
 * @param name - The name of the package.
 * @return The package that corresponds to that name. Will return an empty package if that name does not exist.
 */
Package Database::getInstalledPackageByName(string name) {
    if (installedPackages.count(name))
        return installedPackages[name];
    Package p;
    return p;
}

/**
 * Gets an available package based off its name.
 * @param name - The name of the package to look up.
 * @return The package that corresponds to that name. Will return an empty package if the name does not exist.
 */
Package Database::getAvailablePackageByName(string name) {
    if (packagesAvailable.count(name))
        return packagesAvailable[name];
    Package p;
    return p;
}
