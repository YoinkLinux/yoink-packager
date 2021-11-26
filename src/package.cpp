/*
 * Gavin C. Pease | u1176408 | CS3505
 * Assignment X
 *  Package
 */
#include "package.h"

/**
 * Gets the packageName of this package.
 * @return The packageName of the package.
 */
string Package::getName() {
    return packageName;
}

/**
 * Gets the file (ie, acl-ver.tar.gz) path for downloading.
 * @return The full file packageName.
 */
string Package::getFile() {
    return file;
}

/**
 * Gets when this package was created in the database.
 * @return The version
 */
int Package::getTimestamp() {
    return version;
}

/**
 * Gets all the dependencies for this package.
 * @return The list of dependencies.
 */
std::set<string> Package::getDependencies() {
    return packageDependencies;
}

/**
 * Creates a new package.
 * @param name - The name of the package.
 * @param file - The full package file to download.
 * @param dependencies - The dependencies of the package.
 * @param version - The current version of the package.
 * @param guid - The GUID of the package.
 */
Package::Package(const string &name, const string& file, const vector<string>& dependencies, const int version,
                 const string &guid) {
    this->packageName = name;
    this->file = file;
    this->version = version;
    this->guid = guid;
    for (const string &depends: dependencies)
        packageDependencies.insert(depends);
}

bool Package::operator==(const Package &otherPackage) const {
    return this->packageName == otherPackage.packageName && this->version == otherPackage.version
           && this->version == otherPackage.version && this->file == otherPackage.file;
}

Package::Package() {
    packageName = "";
    file = "";
    version = -1;
    guid = "";
    packageDependencies.clear();
}

