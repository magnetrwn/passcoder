#include "memorable.hpp"

MemorableStringGen::MemorableStringGen(const std::string &stringsFile, const std::string &settingsFile)
    : stringsFile_(stringsFile),
      settingsFile_(settingsFile),
      mt(static_cast<uint>(std::time(nullptr))) {

    const boost::json::object stringsJSON = JSONUtil::readJSON(stringsFile_).as_object();

    adjectives = JSONUtil::getListValues(stringsJSON, "adjectives");
    nouns = JSONUtil::getListValues(stringsJSON, "nouns");
    numbers = JSONUtil::getListValues(stringsJSON, "numbers");
    phonetic = JSONUtil::getListValues(stringsJSON, "phonetic");

    adjVecDist = std::uniform_int_distribution<uint>(0, adjectives.size() - 1);
    nounsVecDist = std::uniform_int_distribution<uint>(0, nouns.size() - 1);
    numbersVecDist = std::uniform_int_distribution<uint>(0, numbers.size() - 1);
    phoneticVecDist = std::uniform_int_distribution<uint>(0, phonetic.size() - 1);

    randUcharDist = std::uniform_int_distribution<unsigned char>(0, 255);

    MemorableStringGen::setToJSONDict("memorable");

    randBoolDist = std::bernoulli_distribution(leetRandLevel);
}

void
MemorableStringGen::setToJSONDict(const std::string &dictName) {
    const boost::json::object settingsJSON = JSONUtil::readJSON(settingsFile_).as_object();
    std::map<std::string, std::string> settingsMap = JSONUtil::getDictMap(settingsJSON, dictName);

    try {
        generate = static_cast<MemorableStringGen::GenSetting>(std::stoul(settingsMap["generate"]));
        leetRandLevel = std::stof(settingsMap["leetRandLevel"]);
        leetEnabled = settingsMap["leetEnabled"] == "1";
        wordCount = std::stoul(settingsMap["wordCount"]);
        totalLength = std::stoul(settingsMap["totalLength"]);

    } catch (const std::exception &ex) {
        throw std::runtime_error(std::string("Error parsing settings map: ") + ex.what());
    }
}

void
MemorableStringGen::storeAsJSONDict(const std::string &dictName) {
    std::map<std::string, std::string> storeMap;
    storeMap["generate"] = std::to_string(generate);
    storeMap["leetRandLevel"] = std::to_string(leetRandLevel);
    storeMap["leetEnabled"] = std::to_string(leetEnabled);
    storeMap["wordCount"] = std::to_string(wordCount);
    storeMap["totalLength"] = std::to_string(totalLength);
    JSONUtil::storeMapAsDict(settingsFile_, dictName, storeMap);
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

MemorableStringGen::GenSetting
MemorableStringGen::ustringToGenSetting(const Glib::ustring &src) {
    for (uint i = 0; i < gensettings; i++)
        if (src == Glib::ustring(genSettingNames[i]))
            return static_cast<GenSetting>(i);
    throw std::runtime_error("Invalid ustring in ustringToGenSetting function call.");
}

std::string
MemorableStringGen::toLeet(const std::string &src) {
    std::string phrase = src;
    char leetReplacements[36] = {
        '4', 'B', 'C', 'D', '3', 'F', 'G', 'H', '1', 'J', 'K', 'L', 'M',
        'N', '0', 'P', 'Q', 'R', '5', '7', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    for (auto &letter : phrase) {
        if (randBoolDist(mt) and std::isalpha(letter))
            letter = leetReplacements[std::tolower(letter) - 'a'];
    }
    return phrase;
}

// Getters and setters

void
MemorableStringGen::setGenerator(const GenSetting setting) {
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

MemorableStringGen::GenSetting
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