//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Raum.h"

/*
 * Konstruktoren
 */

Raum::Raum() {
    this->raumArt = "DummyRaum";
    this->adrBau = 404;
    this->adrRaum = 404;
    this->kapazataet = 0;
}

Raum::Raum(string &art, int adrBau, int adrRaum, int kap) {
    this->raumArt = art;
    this->adrBau = adrBau;
    this->adrRaum = adrRaum;
    this->kapazataet = kap;
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Raum &raum) {
    out << raum.raumArt << ';' << raum.adrBau << '/' << raum.adrRaum << ';' << raum.kapazataet;
    return out;
}

/*
 * Getter
 */

const string &Raum::getRaumArt() const {
    return raumArt;
}

int Raum::getAdrBau() const {
    return adrBau;
}

int Raum::getAdrRaum() const {
    return adrRaum;
}

int Raum::getKapazataet() const {
    return kapazataet;
}

/*______________________________________________________________
 * Methoden:
 */

vector<Raum> Raum::parse(const string& pathToFile) {
    ifstream inputStream(pathToFile);
    if(!inputStream) {
        cerr << "Fehler beim Oeffnen der Datei " << pathToFile << endl;
    }
    cout << "Starte Einlesen von Raumliste!" << endl;

    size_t lines = 0;
    vector<Raum> list;
    string line;
    while (!inputStream.eof()){
        getline(inputStream, line);
        if(line.empty()) break;
        string remove("\"");
        line = Utility::removeChars(line, remove);
        vector<string> splitRaum = Utility::splitString(line, ',');
        vector<string> splitAdr = Utility::splitString(splitRaum[1],'/');
        int adrBau;
        int adrRaum;
        int kap;
        istringstream(splitAdr[0]) >> adrBau;
        istringstream(splitAdr[1]) >> adrRaum;
        istringstream(splitRaum[2]) >> kap;
        Raum a (splitRaum[0], adrBau, adrRaum,kap);
        list.push_back(a);
        ++lines;
    }
    cout << "Raumliste eingelesen! - " << lines << " Zeilen eingelesen" << endl;
    return list;
}
