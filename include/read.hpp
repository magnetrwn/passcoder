#ifndef READ_H_
#define READ_H_

#include <string>
#include <vector>
#include <fstream>

class CSVReader {
public:
    static void readCSV(const std::string &filename, std::vector<std::string> &dest);
};

#endif
