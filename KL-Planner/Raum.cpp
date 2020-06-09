//
// Created by Johnny on 08.06.2020.
//

#include "Raum.h"


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

vector<Raum> Raum::parseRaumliste(const string& pathToFile) {
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
        cout << a << endl;
        ++lines;
    }
    cout << "Raumliste eingelesen! - " << lines << " Zeilen eingelesen" << endl;
    return list;
}

std::ostream &operator<<(ostream &out, const Raum &raum) {
    out << raum.raumArt << ';' << raum.adrBau << '/' << raum.adrRaum << ';' << raum.kapazataet;
    return out;
}