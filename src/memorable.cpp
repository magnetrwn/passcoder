#include "memorable.hpp"

MemorableStringGen::MemorableStringGen(const std::string &adjectivesFile, const std::string &nounsFile,
                                       const std::string &numbersFile, const std::string &phoneticFile)
    : mt(static_cast<unsigned int>(std::time(nullptr))),
      adjectives(CSVUtil::readCSV(adjectivesFile)),
      nouns(CSVUtil::readCSV(nounsFile)),
      numbers(CSVUtil::readCSV(numbersFile)),
      phonetic(CSVUtil::readCSV(phoneticFile)) {

    adjVecDist = std::uniform_int_distribution<unsigned int>(0, adjectives.size() - 1);
    nounsVecDist = std::uniform_int_distribution<unsigned int>(0, nouns.size() - 1);
    numbersVecDist = std::uniform_int_distribution<unsigned int>(0, numbers.size() - 1);
    phoneticVecDist = std::uniform_int_distribution<unsigned int>(0, phonetic.size() - 1);

    // These are set the same as the GtkAdjustment and settings menu widgets
    generate = ADJ_AND_NOUN;
    randBoolDist = std::bernoulli_distribution(0.1667);
    leetEnabled = true;
    count = 10;
    length = 32;
}

void
MemorableStringGen::setGenerator(const genSetting setting) {
    generate = setting;
}

void
MemorableStringGen::setLeet(const bool enable) {
    leetEnabled = enable;
}

void
MemorableStringGen::setRandomness(const float likelihood) {
    randBoolDist = std::bernoulli_distribution(likelihood);
}

void
MemorableStringGen::setCount(const unsigned int value) {
    count = value;
}

void
MemorableStringGen::setLength(const unsigned int value) {
    length = value;
}

std::string
MemorableStringGen::get() {
    std::string phrase, noun;
    switch (generate) {
    case ADJ_AND_NOUN:
        phrase = adjectives[adjVecDist(mt)] + " " + nouns[nounsVecDist(mt)];
        break;
    case PHONETIC_NOUN:
        noun = nouns[nounsVecDist(mt)];
        for (char letter : noun) {
            if (letter == ' ')
                continue;
            phrase += " " + phonetic[letter - 'a'];
        }
        break;
    case PHONETIC:
        phrase += (phonetic[phoneticVecDist(mt)]);
        for (unsigned int i = 0; i < count - 1; i++)
            phrase += " " + phonetic[phoneticVecDist(mt)];
        break;
    case NUMBERS:
        phrase += (numbers[numbersVecDist(mt)]);
        for (unsigned int i = 0; i < count - 1; i++)
            phrase += " " + numbers[numbersVecDist(mt)];
        break;
    case HEXADECIMAL:
        break;
    case ASCII85:
        break;
    default:
        std::cerr << "Invalid generator for MemorableStringGen." << std::endl;
        throw 135;
        break;
    }
    if (leetEnabled)
        return phrase = toLeet(phrase);

    return phrase;
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