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

vector<Raum> Raum::parseRaumliste(string pathToFile) {
    ifstream inputStream(pathToFile);
    if(!inputStream) {
        cerr << "Fehler beim Oeffnen der Datei " << pathToFile << endl;
    }
    size_t lines = 0;
    vector<Raum> list;

    while (!inputStream.eof()){
        string line;
        getline(inputStream, line);
        //TODO list.push_back(parseRaum(line));
        cout << line << "\n";
        ++lines;
    }
    cout << "Done! " << lines << " lines written.\n";
    return list;
}

Raum Raum::parseRaum(string &s) {
    vector<string> splitRaum = Utility::splitString(s, ';');
    int adrBau = stoi(splitRaum[1]);
    int adrRaum = stoi(splitRaum[2]);
    int kap = stoi(splitRaum[3]);
    return Raum(splitRaum[0],adrBau,adrRaum,kap);
}
