#ifndef MEMORABLE_H_
#define MEMORABLE_H_

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include <cctype>

#include "read.hpp"

class MemorableStringGen {
private:
    std::mt19937 mt;

    std::vector<std::string> adjectives;
    std::vector<std::string> nouns;

    std::uniform_int_distribution<unsigned int> adjVecDist;
    std::uniform_int_distribution<unsigned int> nounsVecDist;
    std::bernoulli_distribution randBoolDist;

public:
    MemorableStringGen(const std::string &adjectivesFile, const std::string &nounsFile);
    std::string get();
    std::string getLeet();
};

#endif
