#include <iostream>
#include <yoink.h>

int main() {
    Yoink y;
    set<string> depends = y.resolve_dependencies("acl");
    for(auto package : depends){
        std::cout << package << std::endl;
    }
}

/**
 * Creates a log info based on the level and the output.
 * @param level - The log level to output.
 * @param output - The data to output.
 */
void Yoink::log(Yoink::LogLevel level, const string &output) {
    string type;
    switch (level) {
        case LogLevel::INFO:
            type = "[INFO]";
            break;
        case LogLevel::WARN:
            type = "[WARN]";
            break;
        case LogLevel::ERR:
            type = "[ERROR]";
            break;
        default:
            break;
    }
    printf("%s %s\n", type.c_str(), output.c_str());
}

/**
 * Resolves all of the dependencies
 * @return
 */
set<string> Yoink::resolve_dependencies(string packageName) {
    set<string> deps;
    Package p(availablePackages[packageName]);
    if (p.getName().empty())
        return deps;
    set<string> dependencies(p.getDependencies());
    set<string> my_dependencies = resolve_dependencies_helper(dependencies);
    dependencies.insert(packageName);
    return my_dependencies;
}

/**
 * Resolves all the dependencies from the given list
 * @param dependencies - The initial list of dependencies
 * @return The given dependencies, and the dependencies that they rely on.
 */
set<string> Yoink::resolve_dependencies_helper(set<string> &dependencies) {
    bool added = false;
    while (!added) {
        added = false;
        for (auto dependency: dependencies) {
            if (availablePackages.count(dependency)) {
                auto depList = availablePackages[dependency];
                for (auto _dependency: depList.getDependencies()) {
                    if (dependencies.count(_dependency) < 1) {
                        dependencies.insert(_dependency);
                        added = true;
                    }
                }
            }
        }
    }
    return dependencies;
}

string Yoink::generate_install_command(string packageName, bool reinstall, const string &directory) {
    set<string> toInstall;
    string command;
    if (!reinstall) {
        toInstall = resolve_dependencies(packageName);
        //TODO: Check against installed databased for already installed packages?
    } else {
        toInstall.insert(packageName);
    }
    if (directory.empty())
        command.append(YOINK_DIR).append("yoink-installer ").append("install ");
    else
        command.append(YOINK_DIR).append("yoink-installer ").append("--dir ").append(directory).append(" install ");
    for (auto package: toInstall)
        command.append(package).append(" ");
    log(LogLevel::INFO, command);
    return command;
}

Yoink::Yoink() {
    availablePackages = db.getPackagesAvailable();
    installedPackages = db.getInstalledPackages();
}
