#ifndef READ_H_
#define READ_H_

#include <string>
#include <vector>

// Static method classes, call these utilities when needed
class CSVReader {
public:
    static void readCSV(const std::string &filename, std::vector<std::string> &dest);
};

#endif
