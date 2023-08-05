#include "memorable.hpp"

MemorableStringGen::MemorableStringGen(const std::string &adjectivesFile, const std::string &nounsFile)
    : mt(static_cast<unsigned int>(std::time(nullptr))) {

    CSVReader::readCSV(adjectivesFile, adjectives);
    CSVReader::readCSV(nounsFile, nouns);

    adjVecDist = std::uniform_int_distribution<unsigned int>(0, adjectives.size() - 1);
    nounsVecDist = std::uniform_int_distribution<unsigned int>(0, nouns.size() - 1);
    randBoolDist = std::bernoulli_distribution(0.2222);
}

std::string MemorableStringGen::get() {
    return adjectives[adjVecDist(mt)] + " " + nouns[nounsVecDist(mt)];
}

std::string MemorableStringGen::getLeet() {
    std::string phrase = adjectives[adjVecDist(mt)] + " " + nouns[nounsVecDist(mt)];
    char leetReplacements[36] = {
        '4', 'B', 'C', 'D', '3', 'F', 'G', 'H', '1', 'J', 'K', 'L', 'M',
        'N', '0', 'P', 'Q', 'R', '5', '7', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    for(auto& letter : phrase) {
        if(randBoolDist(mt) and std::isalpha(letter))
            letter = leetReplacements[std::tolower(letter) - 'a'];
    }
    return phrase;
}