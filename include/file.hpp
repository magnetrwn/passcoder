#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

#include <boost/json.hpp>

class CSVUtil {
public:
    static std::vector<std::string> readCSV(const std::string &filename);
};

class JSONUtil {
public:
    static boost::json::value readJSON(const std::string &filename);
    static std::vector<std::string> getListValues(const boost::json::value &parsedValue,
            const std::string &listName);
};

#endif
