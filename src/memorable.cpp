#include "memorable.hpp"
#include "read.hpp"
#include <iostream>
#include <ctime>

MemorableStringGen::MemorableStringGen(const std::string &adjectivesFile, const std::string &nounsFile)
    : mt(static_cast<unsigned int>(std::time(nullptr))) {
    CSVReader::readCSV(adjectivesFile, adjectives);
    CSVReader::readCSV(nounsFile, nouns);
}

std::string MemorableStringGen::get() {
    int adjVecSize = adjectives.size();
    int nounsVecSize = nouns.size();

    if (adjVecSize == 0 || nounsVecSize == 0) {
        std::cerr << "CSV file size is zero." << std::endl;
        throw 131;
    }

    std::uniform_int_distribution<int> adjVecDist(0, adjVecSize - 1);
    std::uniform_int_distribution<int> nounsVecDist(0, nounsVecSize - 1);

    return adjectives[adjVecDist(mt)] + " " + nouns[nounsVecDist(mt)];
}