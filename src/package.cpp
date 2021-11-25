/*
 * Gavin C. Pease | u1176408 | CS3505
 * Assignment X
 *  Package
 */
#include <vector>
#include "package.h"

/**
 * Gets the name of this package.
 * @return The name of the package.
 */
string Package::getName() {
    return name;
}

/**
 * Gets the file (ie, acl-ver.tar.gz) path for downloading.
 * @return The full file name.
 */
string Package::getFile() {
    return file;
}

/**
 * Gets when this package was created in the database.
 * @return The timestamp
 */
int Package::getTimestamp() {
    return timestamp;
}

/**
 * Gets all the dependencies for this package.
 * @return The list of dependencies.
 */
std::set<string> Package::getDependencies() {
    return packageDependencies;
}

/**
 * Creates a new package
 * @param name - The name of the package.
 * @param file - The file for the package.
 * @param timestamp - The timestamp of the package.
 * @param dependencies - The dependencies for the package.
 */
Package::Package(string name, string file, string timestamp, std::vector<string> dependencies) {
    this->name = name;
    this->file = file;
    this->timestamp = stoi(timestamp);
    for (string depends: dependencies)
        packageDependencies.insert(depends);
}

bool Package::operator==(const Package &otherPackage) const {
    return this->name == otherPackage.name && this->timestamp == otherPackage.timestamp
           && this->timestamp == otherPackage.timestamp && this->file == otherPackage.file;
}

Package::Package() {
    name = "";
    file = "";
    timestamp = -1;
    packageDependencies.clear();
}

