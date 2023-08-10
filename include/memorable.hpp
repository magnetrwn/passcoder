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
    void setLeetRandomness(const double likelihood);
    void setWordCount(const uint value);
    void setTotalLength(const uint value);

    genSetting getGenerator() const;
    bool getLeet() const;
    double getLeetRandomness() const;
    uint getWordCount() const;
    uint getTotalLength() const;

    static genSetting ustringToGenSetting(const Glib::ustring &src);

private:
    std::mt19937 mt;

    std::vector<std::string> adjectives, nouns, numbers, phonetic;

    std::uniform_int_distribution<uint> adjVecDist;
    std::uniform_int_distribution<uint> nounsVecDist;
    std::uniform_int_distribution<uint> numbersVecDist;
    std::uniform_int_distribution<uint> phoneticVecDist;

    std::uniform_int_distribution<unsigned char> randUcharDist;
    std::bernoulli_distribution randBoolDist;

    bool leetEnabled;
    uint wordCount, totalLength;
    double leetRandLevel;
    genSetting generate;

    std::string toLeet(const std::string &src);
};

#endif
