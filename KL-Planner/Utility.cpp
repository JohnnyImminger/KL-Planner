//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Exam.h"
#include "Utility.h"

vector<string> Utility::splitString(string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}

string Utility::removeChars(string &s, string &charsToRemove) {
    for (char c: charsToRemove) {
        s.erase(std::remove(s.begin(), s.end(), c), s.end());
    }
    return s;
}

int Utility::getRandomInt(int max) {
    return rand() % max;
}

void Utility::printIgnoredExam(const string& line) {
    ofstream output;
    output.open("../../output/ignoredExams.csv", ios_base::app);
    output << line << endl;
    output.close();
}