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