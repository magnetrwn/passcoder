#include "file.hpp"

std::vector<std::string>
CSVUtil::readCSV(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        throw 133;
    }

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
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        throw 133;
    }

    std::string jsonContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Parse JSON content using Boost.JSON
    boost::json::error_code ec;
    boost::json::value parsedValue = boost::json::parse(jsonContent, ec);
    if (ec) {
        throw std::runtime_error("Failed to parse JSON content: " + ec.message());
    }

    return parsedValue;
}
