#include "memorable.hpp"

MemorableStringGen::MemorableStringGen(const std::string &stringsFile)
    : mt(static_cast<uint>(std::time(nullptr))) {

    const boost::json::object rootJSON = JSONUtil::readJSON(stringsFile).as_object();

    adjectives = JSONUtil::getListValues(rootJSON, "adjectives");
    nouns = JSONUtil::getListValues(rootJSON, "nouns");
    numbers = JSONUtil::getListValues(rootJSON, "numbers");
    phonetic = JSONUtil::getListValues(rootJSON, "phonetic");

    adjVecDist = std::uniform_int_distribution<uint>(0, adjectives.size() - 1);
    nounsVecDist = std::uniform_int_distribution<uint>(0, nouns.size() - 1);
    numbersVecDist = std::uniform_int_distribution<uint>(0, numbers.size() - 1);
    phoneticVecDist = std::uniform_int_distribution<uint>(0, phonetic.size() - 1);

    randUcharDist = std::uniform_int_distribution<unsigned char>(0, 255);

    // These are set the same as the GtkAdjustment and settings menu widgets
    generate = ADJ_AND_NOUN;
    leetRandLevel = 0.167;
    leetEnabled = true;
    wordCount = 10;
    totalLength = 32;

    randBoolDist = std::bernoulli_distribution(leetRandLevel);
}

std::string
MemorableStringGen::get() {
    std::string phrase, noun;
    bool firstLetter = true;
    char hexCharacters[16] = {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };

    switch (generate) {
    case ADJ_AND_NOUN:
        phrase = adjectives[adjVecDist(mt)] + " " + nouns[nounsVecDist(mt)];
        break;
    case PHONETIC_NOUN:
        noun = nouns[nounsVecDist(mt)];
        for (char letter : noun) {
            if (letter == ' ')
                continue;
            if (firstLetter) {
                phrase += phonetic[letter - 'a'];
                firstLetter = false;
            } else
                phrase += " " + phonetic[letter - 'a'];
        }
        break;
    case PHONETIC:
        phrase += (phonetic[phoneticVecDist(mt)]);
        for (uint i = 0; i < wordCount - 1; i++)
            phrase += " " + phonetic[phoneticVecDist(mt)];
        break;
    case NUMBERS:
        phrase += (numbers[numbersVecDist(mt)]);
        for (uint i = 0; i < wordCount - 1; i++)
            phrase += " " + numbers[numbersVecDist(mt)];
        break;
    case HEXADECIMAL:
        for (uint i = 0; i < totalLength; i++)
            phrase += hexCharacters[randUcharDist(mt) % 16];
        break;
    case ASCII:
        for (uint i = 0; i < totalLength; i++)
            phrase += static_cast<char>(randUcharDist(mt) % 93 + 33);
        break;
    default:
        throw std::runtime_error("Invalid generator for MemorableStringGen.");
    }
    if (leetEnabled)
        return phrase = toLeet(phrase);

    return phrase;
}

MemorableStringGen::genSetting
MemorableStringGen::ustringToGenSetting(const Glib::ustring &src) {
    MemorableStringGen::genSetting gen;

    if (src == Glib::ustring("ADJ_AND_NOUN"))
        gen = MemorableStringGen::ADJ_AND_NOUN;
    else if (src == Glib::ustring("PHONETIC_NOUN"))
        gen = MemorableStringGen::PHONETIC_NOUN;
    else if (src == Glib::ustring("PHONETIC"))
        gen = MemorableStringGen::PHONETIC;
    else if (src == Glib::ustring("NUMBERS"))
        gen = MemorableStringGen::NUMBERS;
    else if (src == Glib::ustring("HEXADECIMAL"))
        gen = MemorableStringGen::HEXADECIMAL;
    else if (src == Glib::ustring("ASCII"))
        gen = MemorableStringGen::ASCII;
    else
        throw std::runtime_error("Invalid ustring in ustringToGenSetting function call.");

    return gen;
}

std::string
MemorableStringGen::toLeet(const std::string &src) {
    std::string phrase = src;
    char leetReplacements[36] = {
        '4', 'B', 'C', 'D', '3', 'F', 'G', 'H', '1', 'J', 'K', 'L', 'M',
        'N', '0', 'P', 'Q', 'R', '5', '7', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    for (auto& letter : phrase) {
        if (randBoolDist(mt) and std::isalpha(letter))
            letter = leetReplacements[std::tolower(letter) - 'a'];
    }
    return phrase;
}

// Getters and setters

void
MemorableStringGen::setGenerator(const genSetting setting) {
    generate = setting;
}

void
MemorableStringGen::setLeet(const bool enable) {
    leetEnabled = enable;
}

void
MemorableStringGen::setLeetRandomness(const double likelihood) {
    if (likelihood < 0.0 || likelihood > 1.0)
        return;
    leetRandLevel = likelihood;
    randBoolDist = std::bernoulli_distribution(likelihood);
}

void
MemorableStringGen::setWordCount(const uint value) {
    wordCount = value;
}

void
MemorableStringGen::setTotalLength(const uint value) {
    totalLength = value;
}

MemorableStringGen::genSetting
MemorableStringGen::getGenerator() const {
    return generate;
}

bool
MemorableStringGen::getLeet() const {
    return leetEnabled;
}

double
MemorableStringGen::getLeetRandomness() const {
    return leetRandLevel;
}

uint
MemorableStringGen::getWordCount() const {
    return wordCount;
}

uint
MemorableStringGen::getTotalLength() const {
    return totalLength;
}