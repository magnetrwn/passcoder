#include "file.hpp"

std::vector<std::string>
CSVUtil::readCSV(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file.");

    std::vector<std::string> destVector;

    std::string line;
    while (std::getline(file, line)) {
        destVector.push_back(line);
    }

    return destVector;
}

boost::json::value
JSONUtil::readJSON(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file.");

    std::string jsonContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    boost::json::error_code ec;
    boost::json::value jsonValue = boost::json::parse(jsonContent, ec);
    if (ec)
        throw std::runtime_error("Failed to parse JSON content: " + ec.message());

    return jsonValue;
}

std::vector<std::string>
JSONUtil::getListValues(const boost::json::value &jsonValue, const std::string &listName) {
    std::vector<std::string> values;

    boost::json::error_code ec;
    const boost::json::object &rootObject = jsonValue.as_object();
    const boost::json::array &list = rootObject.at(listName).as_array();

    if (ec)
        throw std::runtime_error("Error accessing JSON list: " + ec.message());

    for (const auto &element : list) {
        values.push_back(boost::json::value_to<std::string>(element));

        if (ec)
            throw std::runtime_error("Error parsing JSON list: " + ec.message());
    }

    return values;
}

std::map<std::string, std::string>
JSONUtil::getDictMap(const boost::json::value &jsonValue, const std::string &dictName) {
    std::map<std::string, std::string> dictMap;

    boost::json::object rootObject;
    boost::json::object dictObject;
    try {
        rootObject = jsonValue.as_object();
        dictObject = rootObject.at(dictName).as_object();
    } catch (boost::wrapexcept<std::out_of_range> &ex) {
        throw std::runtime_error(std::string("Error accessing JSON dictionary or invalid name: ") + ex.what());
    }

    boost::json::error_code ec;
    for (const auto &entry : dictObject) {
        dictMap[entry.key()] = boost::json::value_to<std::string>(entry.value());

        if (ec)
            throw std::runtime_error("Error parsing JSON dictionary: " + ec.message());
    }

    return dictMap;
}

void
JSONUtil::storeMapAsDict(const std::string &filename, const std::string &dictName,
                         const std::map<std::string, std::string> &dictMap) {

    // TODO: ugly, will reformat
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Unable to open file for reading: " + filename);
    }

    std::string fileContent((std::istreambuf_iterator<char>(inputFile)),
                            std::istreambuf_iterator<char>());
    inputFile.close();

    boost::json::value jsonValue = boost::json::parse(fileContent);

    boost::json::object jsonObject = jsonValue.as_object();

    if (jsonObject.find(dictName) == jsonObject.end()) {
        throw std::runtime_error("Dictionary '" + dictName + "' not found in JSON.");
    }

    boost::json::object &dictObject = jsonObject[dictName].as_object();

    for (const auto &entry : dictMap) {
        dictObject[entry.first] = boost::json::value(entry.second);
    }

    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Unable to open file for writing: " + filename);
    }

    outputFile << jsonObject;
    outputFile.close();
}

/*
void
JSONUtil::storeMapAsDict(const std::string &filename, const std::string &dictName,
                         const std::map<std::string, std::string> &dictMap) {
    boost::json::object jsonObject;

    for (const auto &entry : dictMap) {
        jsonObject[entry.first] = entry.second;
    }

    boost::json::value jsonValue = jsonObject;

    std::ofstream file(filename);
    if (file.is_open()) {
        file << jsonValue;
        file.close();
    } else
        throw std::runtime_error("Unable to open file for writing: " + filename);
}
*/