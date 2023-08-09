#ifndef MEMORABLE_H_
#define MEMORABLE_H_

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include <cctype>

#include "file.hpp"

class MemorableStringGen {
private:
    std::mt19937 mt;

    std::vector<std::string> adjectives, nouns, numbers, phonetic;

    std::uniform_int_distribution<unsigned int> adjVecDist;
    std::uniform_int_distribution<unsigned int> nounsVecDist;
    std::uniform_int_distribution<unsigned int> numbersVecDist;
    std::uniform_int_distribution<unsigned int> phoneticVecDist;
    std::bernoulli_distribution randBoolDist;

    bool leetEnabled;
    unsigned int count, length;
    enum genSetting { ADJ_AND_NOUN, PHONETIC_NOUN, PHONETIC, NUMBERS, HEXADECIMAL, ASCII85, gensettings };
    genSetting generate;

    std::string toLeet(const std::string &src);

public:
    MemorableStringGen(const std::string &adjectivesFile, const std::string &nounsFile,
                       const std::string &numbersFile, const std::string &phoneticFile);
    std::string get();
    void setGenerator(const genSetting setting);
    void setLeet(const bool enable);
    void setRandomness(const float likelihood);
    void setCount(const unsigned int value);
    void setLength(const unsigned int value);
};

#endif
