#include "read.hpp"

void CSVReader::readCSV(const std::string &filename, std::vector<std::string> &dest) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        dest.push_back(line);
    }
}
