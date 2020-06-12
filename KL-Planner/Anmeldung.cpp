//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Anmeldung.h"

/*
 * Konstruktoren
 */

Anmeldung::Anmeldung() {
    this->studMatrikelNr = 404;
    this->studStudiengang = "dummyAnmeldung";
    this->klausurVersion = 404;
    this->klausurNummer = 404;
    this->klausurForm = "dummyAnmeldung";
    this->klausurFormText = "dummyAnmeldung";
    this->klausurSemester = 404;
}

Anmeldung::Anmeldung(int matrikelNr, string &studiengang, int pVersion, int pNummer, string &pForm, string &dText,
                     int pSemester) {
    this->studMatrikelNr = matrikelNr;
    this->studStudiengang = studiengang;
    this->klausurVersion = pVersion;
    this->klausurNummer = pNummer;
    this->klausurForm = pForm;
    this->klausurFormText = dText;
    this->klausurSemester = pSemester;
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Anmeldung &anmeldung) {
    out << anmeldung.getMatrikelNr() << ';' << anmeldung.getStudiengang() << ';' << anmeldung.getKlausurVersion() << ';' << anmeldung.getKlausurNummer() << ';' << anmeldung.getKlausurForm() << ';' << anmeldung.getKlausurFormText() << ';' << anmeldung.getKlausurSemester();
    return out;
}

/*
 * Getter
 */

int Anmeldung::getMatrikelNr() const {
    return studMatrikelNr;
}

const string &Anmeldung::getStudiengang() const {
    return studStudiengang;
}

int Anmeldung::getKlausurVersion() const {
    return klausurVersion;
}

int Anmeldung::getKlausurNummer() const {
    return klausurNummer;
}

const string &Anmeldung::getKlausurForm() const {
    return klausurForm;
}

const string &Anmeldung::getKlausurFormText() const {
    return klausurFormText;
}

int Anmeldung::getKlausurSemester() const {
    return klausurSemester;
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
    input.close();
    cout << lines << " Anmeldungen eingelesen" << endl;
    return list;
}








