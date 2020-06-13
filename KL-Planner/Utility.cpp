//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
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

int Utility::getRandomInt(int max) {
    return rand() % max;
}

bool Utility::vectorContains(vector<int> &list, int element) {
    for (int i : list) {
        if (i == element){
            return true;
        }
    }
    return false;
}

vector<int> Utility::findShortestArray(vector<vector<int>> &list) {
    int minSize = 404040404;
    int minSizeIndex = -1;
    for (int i = 0; i < list.size(); ++i) {
        int vectorSize = list.at(i).size();
        if (vectorSize < minSize){
            minSize = vectorSize;
            minSizeIndex = i;
        }
    }
    return list.at(minSizeIndex);
}

int Utility::findShortestArrayIndex(vector <vector<int>> &list) {
    int minSize = 404040404;
    int minSizeIndex = -1;
    for (int i = 0; i < list.size(); ++i) {
        int vectorSize = list.at(i).size();
        if (vectorSize < minSize){
            minSize = vectorSize;
            minSizeIndex = i;
        }
    }
    return minSizeIndex;
}
