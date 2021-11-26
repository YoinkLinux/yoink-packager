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
#include <vector>

using std::string;
using std::set;
using std::vector;

class Package {
    public:

    private:
        string packageName;
        string file;
        string guid;
        int version;
        set<string> packageDependencies;
    public:
        string getName();
        string getFile();
        int getTimestamp();
        std::set<string> getDependencies();
        Package(const string &name, const string& file, const vector<string>& dependencies, const int version,
                const string &guid);
        Package();
        bool operator==(const Package &otherPackage) const;

        struct PackageHash {
            size_t operator()(const Package &p) const {
                return std::hash<std::string>()(p.file);
            }
        };
};


#endif //YOINK_PACKAGE_H
