//
// Created by Johnny on 08.06.2020.
//

#include "Anmeldung.h"
#include "Utility.h"
#include <iostream>

vector<Anmeldung> Anmeldung::parse(string filename) {
    ifstream input(filename);
    if(!input) {
        cerr << "Fehler beim Oeffnen der Datei " << filename << endl;
    }
    vector<Anmeldung> list;
    string line;
    while (!input.eof()){
        getline(input, line);
        vector<string> split = Utility::splitString(line, ';');
        int matNr;
        int pVer;
        int pNr;
        int pSem;
        istringstream(split[0]) >> matNr;
        istringstream(split[2]) >> pVer;
        istringstream(split[3]) >> pNr;
        istringstream(split[6]) >> pSem;
        Anmeldung a(matNr, split[1], pVer, pNr, split[4], split[5], pSem);
        list.push_back(a);
        cout << a << endl;
    }
    cout << "Anmeldungen eingelesen!" << endl;
    return list;
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
