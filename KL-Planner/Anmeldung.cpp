//
// Created by Johnny on 08.06.2020.
//

#include "Anmeldung.h"


Anmeldung::Anmeldung() {
    this->matrikelNr = 404;
    this->studiengang = "dummyAnmeldung";
    this->pVersion = 404;
    this->pNummer = 404;
    this->pForm = "dummyAnmeldung";
    this->dText = "dummyAnmeldung";
    this->pSemester = 404;
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


vector<Anmeldung> Anmeldung::parse(const string& filename) {
    ifstream input(filename);
    if(!input) {
        cerr << "Fehler beim Oeffnen der Datei " << filename << endl;
    }
    cout << "Starte Einlesen von Anmeldungen!" << endl;

    size_t lines = 0;
    vector<Anmeldung> list;
    string line;
    getline(input, line);
    while (!input.eof()) {
        getline(input, line);
        if(line.empty()) break;
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
        ++lines;
    }
    cout << "Anmeldungen eingelesen! - " << lines << "Zeilen eingelesen" << endl;
    return list;
}


std::ostream &operator<<(ostream &out, const Anmeldung &anmeldung) {
    out << anmeldung.matrikelNr << ';' << anmeldung.studiengang << ';' << anmeldung.pVersion << ';' << anmeldung.pNummer << ';' << anmeldung.pForm << ';' << anmeldung.dText << ';' << anmeldung.pSemester;
    return out;
}

