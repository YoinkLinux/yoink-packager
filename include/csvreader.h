/*
 * Gavin C. Pease | u1176408 | CS3505
 * Assignment X
 *  csvreader
 */
#ifndef YOINK_CSVREADER_H
#define YOINK_CSVREADER_H
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <sstream>

using std::string;

class csvreader {
    public:
        static std::set<std::vector<std::string>> readFromFile(const char *filename);
        static std::vector<string> splitter(const string &line, char delimiter);
        static string stripEndOfLine(string line);

};


#endif //YOINK_CSVREADER_H
