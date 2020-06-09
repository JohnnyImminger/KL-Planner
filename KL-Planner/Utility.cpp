//
// Created by stein on 08.06.2020.
//

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
