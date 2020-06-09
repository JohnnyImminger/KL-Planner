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

/*
 * Vorgaben durch die Aufgabenstellung
 */

float Utility::klausurPauseProf() {
    return 0.5;
}

float Utility::klausurPauseStudent() {
    return 4;
}

float Utility::klausurPauseRaum() {
    return 1;
}

int Utility::maxKlausurenStudentProTag() {
    return 2;
}

float Utility::startZeitKlausurTag() {
    return 8;
}

float Utility::endZeitKlausurTag() {
    return 18;
}

float Utility::klausurTimeSlot() {
    return endZeitKlausurTag() - startZeitKlausurTag();
}

int Utility::klausurTage() {
    return 9;
}

