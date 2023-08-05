#include "memorable.hpp"
#include "read.hpp"
#include <iostream>
#include <ctime>

MemorableStringGen::MemorableStringGen(const std::string &adjectivesFile, const std::string &nounsFile)
    : mt(static_cast<unsigned int>(std::time(nullptr))) {

    CSVReader::readCSV(adjectivesFile, adjectives);
    CSVReader::readCSV(nounsFile, nouns);

    adjVecDist = std::uniform_int_distribution<unsigned int>(0, adjectives.size() - 1);
    nounsVecDist = std::uniform_int_distribution<unsigned int>(0, nouns.size() - 1);
    randBoolDist = std::bernoulli_distribution(0.16667);
}

std::string MemorableStringGen::get() {
    return adjectives[adjVecDist(mt)] + " " + nouns[nounsVecDist(mt)];
}

std::string MemorableStringGen::getLeet() {
    std::string phrase = adjectives[adjVecDist(mt)] + " " + nouns[nounsVecDist(mt)];
    for(auto& letter : phrase) {
        if(randBoolDist(mt))
            switch(letter) {
                case 'a':
                case 'A':
                    letter = '4';
                    break;
                case 'e':
                case 'E':
                    letter = '3';
                    break;
                case 'i':
                case 'I':
                    letter = '1';
                    break;
                case 'o':
                case 'O':
                    letter = '0';
                    break;
                case 's':
                case 'S':
                    letter = '5';
                    break;
                case 't':
                case 'T':
                    letter = '7';
                    break;
            }
    }
    return phrase;
}