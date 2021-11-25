/*
 * Gavin C. Pease
 * csvreader
 */
#include "csvreader.h"

/**
 * Reads teh given CSV file data, and extracts the first four fields and puts them in a set.
 * @param filename - The file to read
 * @return A set of all entries in the file.
 */
std::set<std::vector<std::string>> csvreader::readFromFile(const char *filename) {
    std::ifstream file(filename);
    std::set<std::vector<std::string>> fileData;
    if (file.is_open()) {
        string line;
        while (std::getline(file, line)) {
            line = stripEndOfLine(line);
            auto splitted = splitter(line, ',');
            if (splitted.size() == 4)
                fileData.insert(splitted);
        }
    }
    file.close();
    return fileData;
}

/**
 * Strips the EOL character from the given line.
 * @param line The line to strip the EOL character.
 * @return A string without any end of line characters.
 */
string csvreader::stripEndOfLine(string line) {
    if (line[line.length() - 1] == '\r')
        line.erase(line.length() - 1);
    if (line[line.length() - 1] == '\n')
        line.erase(line.length() - 1);
    return line;
}

/**
 * Splits the given line based on the delimiter.
 * @param line - The line we want to split.
 * @param delimiter - The delimiter used to split the line.
 * @return A vector of strings split based off the delimiter.
 */
std::vector<string> csvreader::splitter(const string &line, char delimiter) {
    std::vector<string> result;
    std::stringstream ss(line);
    string item;
    while (getline(ss, item, delimiter))
        result.push_back(item);
    return result;
}
