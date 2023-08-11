#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <stdexcept>

#include <boost/json.hpp>
#include <boost/json/error.hpp>

class CSVUtil {
public:
    static std::vector<std::string> readCSV(const std::string &filename);
};

class JSONUtil {
public:
    static boost::json::value readJSON(const std::string &filename);
    static std::vector<std::string> getListValues(const boost::json::value &jsonValue, const std::string &listName);
    static std::map<std::string, std::string> getDictMap(const boost::json::value &jsonValue, const std::string &dictName);
    static void storeMapAsDict(const std::string &filename, const std::string &dictName,
                               const std::map<std::string, std::string> &dictMap);
};

#endif
