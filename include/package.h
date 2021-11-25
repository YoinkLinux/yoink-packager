/*
 * Gavin C. Pease | u1176408 | CS3505
 * Assignment X
 *  Package
 */
#ifndef YOINK_PACKAGE_H
#define YOINK_PACKAGE_H

#include <string>
#include <set>
#include <unordered_map>

using std::string;

class Package {
    public:

    private:
        string name;
        string file;
        int timestamp;
        std::set<string> packageDependencies;
    public:
        string getName();
        string getFile();
        int getTimestamp();
        std::set<string> getDependencies();
        Package(string name, string file, string timestamp, std::vector<string> dependencies);
        Package();
        bool operator==(const Package &otherPackage) const;

        struct PackageHash {
            size_t operator()(const Package &p) const {
                return std::hash<std::string>()(p.file);
            }
        };
};


#endif //YOINK_PACKAGE_H
