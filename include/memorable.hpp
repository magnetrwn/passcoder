#ifndef MEMORABLE_H_
#define MEMORABLE_H_

#include <string>
#include <vector>
#include <random>

class MemorableStringGen {
private:
    std::vector<std::string> adjectives;
    std::vector<std::string> nouns;
    std::mt19937 mt;

public:
    MemorableStringGen(const std::string &adjectivesFile, const std::string &nounsFile);
    std::string get();
};

#endif
