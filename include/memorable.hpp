#ifndef MEMORABLE_H_
#define MEMORABLE_H_

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include <cctype>

#include <glibmm/ustring.h>

#include "file.hpp"

class MemorableStringGen {
public:
    MemorableStringGen(const std::string &adjectivesFile, const std::string &nounsFile,
                       const std::string &numbersFile, const std::string &phoneticFile);
    enum genSetting { ADJ_AND_NOUN, PHONETIC_NOUN, PHONETIC, NUMBERS, HEXADECIMAL, ASCII, gensettings };

    std::string get();

    void setGenerator(const genSetting setting);
    void setLeet(const bool enable);
    void setRandomness(const double likelihood);
    void setWordCount(const unsigned int value);
    void setTotalLength(const unsigned int value);

    static genSetting ustringToGenSetting(const Glib::ustring &src);

private:
    std::mt19937 mt;

    std::vector<std::string> adjectives, nouns, numbers, phonetic;

    std::uniform_int_distribution<unsigned int> adjVecDist;
    std::uniform_int_distribution<unsigned int> nounsVecDist;
    std::uniform_int_distribution<unsigned int> numbersVecDist;
    std::uniform_int_distribution<unsigned int> phoneticVecDist;

    std::uniform_int_distribution<unsigned char> randUcharDist;
    std::bernoulli_distribution randBoolDist;

    bool leetEnabled;
    unsigned int wordCount, totalLength;
    genSetting generate;

    std::string toLeet(const std::string &src);
};

#endif
