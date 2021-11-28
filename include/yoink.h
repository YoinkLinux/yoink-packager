#ifndef YOINK_PACKAGER_YOINK_H
#define YOINK_PACKAGER_YOINK_H

#include <unordered_set>
#include <string>
#include <vector>
#include <map>
#include "package.h"
#include "database.h"
#include <sstream>
#include <iostream>

using std::string;
using std::set;

class Yoink {
    private:
        std::map<string, Package> availablePackages;
        std::map<string, Package> installedPackages;
        const char *YOINK_DIR = "/etc/yoink/";
        const char *YOINK_DB = "/etc/yoink/db/yoink.db";
        const char *INSTALLED_DB = "/etc/yoink/db/installed.db";
        set<string> resolve_dependencies_helper(set<string> &dependencies);
        Database installedPackagesDatabase;
        Database availablePackagesDatabase;
    public:
        enum LogLevel {
            INFO,
            WARN,
            ERR
        };

        Yoink();

        static void log(LogLevel level, const string &output);
        set<string> resolve_dependencies(string packageName);
        string generate_install_command(string packageName, bool reinstall = false, const string &directory = "");
};

#endif//YOINK_PACKAGER_YOINK_H
