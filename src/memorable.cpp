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

    randUcharDist = std::uniform_int_distribution<unsigned char>(0, 255);

    // These are set the same as the GtkAdjustment and settings menu widgets
    generate = ADJ_AND_NOUN;
    randBoolDist = std::bernoulli_distribution(0.167);
    leetEnabled = true;
    wordCount = 10;
    totalLength = 32;
}

void
MemorableStringGen::setGenerator(const genSetting setting) {
#ifdef DEBUG
    std::cerr << "Debug: Generator Setting: " << static_cast<int>(setting) << std::endl;
#endif
    generate = setting;
}

void
MemorableStringGen::setLeet(const bool enable) {
#ifdef DEBUG
    std::cerr << "Debug: Leet Enabled: " << enable << std::endl;
#endif
    leetEnabled = enable;
}

void
MemorableStringGen::setRandomness(const double likelihood) {
    if (likelihood < 0.0 or likelihood > 1.0)
        return;
#ifdef DEBUG
    std::cerr << "Debug: Likelihood: " << likelihood << std::endl;
#endif
    randBoolDist = std::bernoulli_distribution(likelihood);
}

void
MemorableStringGen::setWordCount(const unsigned int value) {
#ifdef DEBUG
    std::cerr << "Debug: Word Count: " << value << std::endl;
#endif
    wordCount = value;
}

void
MemorableStringGen::setTotalLength(const unsigned int value) {
#ifdef DEBUG
    std::cerr << "Debug: Total Length: " << value << std::endl;
#endif
    totalLength = value;
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
        for (int i = 0; i < wordCount - 1; i++)
            phrase += " " + phonetic[phoneticVecDist(mt)];
        break;
    case NUMBERS:
        phrase += (numbers[numbersVecDist(mt)]);
        for (int i = 0; i < wordCount - 1; i++)
            phrase += " " + numbers[numbersVecDist(mt)];
        break;
    case HEXADECIMAL:
        for (int i = 0; i < totalLength; i++)
            phrase += hexCharacters[randUcharDist(mt) % 16];
        break;
    case ASCII:
        for (int i = 0; i < totalLength; i++)
            phrase += static_cast<char>(randUcharDist(mt) % 93 + 33);
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
    else {
        std::cerr << "Invalid ustring in ustringToGenSetting function call." << std::endl;
        throw 136;
    }

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