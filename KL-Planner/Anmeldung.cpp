//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Anmeldung.h"

/*
 * Konstruktoren
 */

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

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Anmeldung &anmeldung) {
    out << anmeldung.matrikelNr << ';' << anmeldung.studiengang << ';' << anmeldung.pVersion << ';' << anmeldung.pNummer << ';' << anmeldung.pForm << ';' << anmeldung.dText << ';' << anmeldung.pSemester;
    return out;
}

/*
 * Getter
 */

int Anmeldung::getMatrikelNr() const {
    return matrikelNr;
}

const string &Anmeldung::getStudiengang() const {
    return studiengang;
}

int Anmeldung::getPVersion() const {
    return pVersion;
}

int Anmeldung::getPNummer() const {
    return pNummer;
}

const string &Anmeldung::getPForm() const {
    return pForm;
}

const string &Anmeldung::getDText() const {
    return dText;
}

int Anmeldung::getPSemester() const {
    return pSemester;
}

/*______________________________________________________________
 * Methoden:
 */

vector<Anmeldung> Anmeldung::parse(const string& filename) {
    ifstream input(filename);
    if(!input) {
        cerr << "Fehler beim Oeffnen der Datei " << filename << endl;
    }

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
        ++lines;
    }
    cout << lines << " Anmeldungen eingelesen" << endl;
    return list;
}








