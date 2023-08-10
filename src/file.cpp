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
    boost::json::value parsedValue = boost::json::parse(jsonContent, ec);
    if (ec)
        throw std::runtime_error("Failed to parse JSON content: " + ec.message());

    return parsedValue;
}

std::vector<std::string>
JSONUtil::getListValues(const boost::json::value &parsedValue, const std::string &listName) {
    std::vector<std::string> values;

    boost::json::error_code ec;
    const boost::json::object &rootObject = parsedValue.as_object();
    const boost::json::array &list = rootObject.at(listName).as_array();

    if (ec)
        throw std::runtime_error("Error accessing JSON list: " + ec.message());

    for (const auto& element : list) {
        values.push_back(boost::json::value_to<std::string>(element));

        if (ec)
            throw std::runtime_error("Error parsing JSON list: " + ec.message());
    }

    return values;
}
