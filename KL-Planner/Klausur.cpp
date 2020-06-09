//
// Created by Johnny on 08.06.2020.
//

#include "Klausur.h"

Klausur::Klausur() {
    this->studiengang = "DummyPruefung";
    this->verteilt = 404;
    this->pVersion = 404;
    this->pNummer = 404;
    this->pName = "DummyPruefung";
    this->pPruefer1 = 404;
    this->pruefer1 = "DummyPruefung";
    this->pPruefer2 = 404;
    this->pruefer2 = "DummyPruefung";
    this->pDauer = 0;
    this->pForm = "DummyPruefung";
    this->pSemester = 404;
    this->angeboten = false;
}

Klausur::Klausur(string& studiengang, int verteilt, int pVersion, int pNummer, string& pName, int pPruefer1,
                 string& pruefer1, int pPruefer2, string& pruefer2, float pDauer, string& pForm, int pSemester,
                 bool angeboten) {
    this->studiengang = studiengang;
    this->verteilt = verteilt;
    this->pVersion = pVersion;
    this->pNummer = pNummer;
    this->pName = pName;
    this->pPruefer1 = pPruefer1;
    this->pruefer1 = pruefer1;
    this->pPruefer2 = pPruefer2;
    this->pruefer2 = pruefer2;
    this->pDauer = pDauer;
    this->pForm = pForm;
    this->pSemester = pSemester;
    this->angeboten = angeboten;

}

vector<Klausur> Klausur::parse(string pathToFile) {
    ifstream input(pathToFile);
    if(!input) {
        cerr << "Fehler beim Oeffnen der Datei " << pathToFile << endl;
    }
    cout << "Starte Einlesen von Pruefungen!" << endl;

    size_t lines = 0;
    vector<Klausur> list;
    string line;
    int index = 0;
    while (!input.eof()){
        getline(input, line);
        if(line.empty()) break;
        vector<string> split = Utility::splitString(line, ';');
        int verteilt;
        int pVersion;
        int pNummer;
        int pPruefer1;
        int pPruefer2;
        float pDauer;
        int pSemeser;
        bool angeboten;
        istringstream(split[1]) >> verteilt;
        istringstream(split[2]) >> pVersion;
        istringstream(split[3]) >> pNummer;
        istringstream(split[5]) >> pPruefer1;
        istringstream(split[7]) >> pPruefer2;
        istringstream(split[9]) >> pDauer;
        istringstream(split[11]) >> pSemeser;
        angeboten = split[12] == "J";
        Klausur a(split[0], verteilt, pVersion, pNummer, split[4], pPruefer1, split[6], pPruefer2,
                  split[8], pDauer, split[10], pSemeser, angeboten);
        a.setIndex(index);
        list.push_back(a);
        ++lines;
        index++;
    }
    cout << "Pruefungen eingelesen! - " << lines << "Zeilen eingelesen" << endl;
    return list;
}

void Klausur::collectAnmeldungen(vector<Anmeldung>& anmeldungenListe) {
    int counter = 0;
    for (auto& anmeldung : anmeldungenListe){
        //TODO muss pNummer und pVersion identisch sein?
        if (anmeldung.getPNummer() == this->pNummer && anmeldung.getPVersion() == this->pVersion){
            this->anmeldungen.push_back(anmeldung);
            counter++;
        }
    }
    this->anzTeilnehmer = counter;
    cout << "Added " << counter << "Anmeldungen zu Prüfung " << this->pName << endl;
}



std::ostream &operator<<(ostream &out, const Klausur &pruefung) {
    out << pruefung.studiengang << ';' << pruefung.verteilt << ';' << pruefung.pVersion << ';' << pruefung.pNummer << ';'
    << pruefung.pName << ';' << pruefung.pPruefer1<< ';' << pruefung.pruefer1 << ';' << pruefung.pPruefer2 << ';'
    << pruefung.pruefer2 << ';' << pruefung.pDauer << ';' << pruefung.pForm << ';' << pruefung.pSemester << ';'
    << pruefung.angeboten;
    return out;
}

const string &Klausur::getStudiengang() const {
    return studiengang;
}

int Klausur::getVerteilt() const {
    return verteilt;
}

int Klausur::getPVersion() const {
    return pVersion;
}

int Klausur::getPNummer() const {
    return pNummer;
}

const string &Klausur::getPName() const {
    return pName;
}

int Klausur::getPPruefer1() const {
    return pPruefer1;
}

const string &Klausur::getPruefer1() const {
    return pruefer1;
}

int Klausur::getPPruefer2() const {
    return pPruefer2;
}

const string &Klausur::getPruefer2() const {
    return pruefer2;
}

float Klausur::getPDauer() const {
    return pDauer;
}

const string &Klausur::getPForm() const {
    return pForm;
}

int Klausur::getPSemester() const {
    return pSemester;
}

bool Klausur::isAngeboten() const {
    return angeboten;
}

const vector<Anmeldung> &Klausur::getAnmeldungen() const {
    return anmeldungen;
}

int Klausur::getIndex() {
    return 0;
}

void Klausur::setIndex(int index) {
    this->index = index;
}

int Klausur::getAnzTeilnehmer() const {
    return anzTeilnehmer;
}


