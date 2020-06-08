//
// Created by Johnny on 08.06.2020.
//

#include "Anmeldung.h"
#include <fstream>
#include <iostream>
#include <sstream>

vector<Anmeldung> Anmeldung::parse(string &filename) {
    ifstream input(filename);
    if(!input) {
        cerr << "Fehler beim Oeffnen der Datei " << filename << endl;
    }
    vector<Anmeldung> list;
    string line;
    while (!input.eof()){
        getline(input, line);
        vector<string> split = split(line, ';');
        Anmeldung a(stoi(split[0]), split[1], stoi(split[2]), stoi(split[3]), split[4], split[5], stoi(split[0]));
        list.push_back(a);
    }

}

Anmeldung::Anmeldung(int matrikelNr, string &studiengang, int pVersion, int pNummer, string &pForm, string &dText,
                     int pSemester) {
    this->matrikelNr = matrikelNr;
    this->studiengang = studiengang;
    this->pVersion = pVersion;
    this->pNummer = pNummer;
    this->pForm = pForm;
    this->dText = dText;
    this->pSemester = pSemester;
}

std::ostream &operator<<(ostream &out, const Anmeldung &anmeldung) {
    out << anmeldung.matrikelNr << ';' << anmeldung.studiengang << ';' << anmeldung.pVersion << ';' << anmeldung.pNummer << ';' << anmeldung.pForm << ';' << anmeldung.dText << ';' << anmeldung.pSemester;
    return out;
}

vector<string> Anmeldung::split(string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}
