//
// Created by Johnny on 08.06.2020.
//

#include "ReadInput.h"

vector<Pruefung> *ReadInput::getPruefungen() {
    return nullptr;
}

vector<Professor> ReadInput::createProfs() {
    vector<Professor> profs;
    vector<Pruefung> klausuren = *ReadInput::getPruefungen();
    for (Pruefung klausur: klausuren) {
        if (klausur.getPPruefer1() != 0) {
            int index = isProfInVector(profs, klausur.getPPruefer1());
            if (index >= 0) {
                profs.at(index).addPruefung(klausur.getIndex());
            } else {

            }
        }
        if (klausur.getPPruefer2() != 0) {

        }
    }

    return profs;
}

int ReadInput::isProfInVector(vector<Professor> &profs, int nr) {
    int index = -1;
    for (int i = 0; i < profs.size(); ++i) {
        if(profs.at(i).getIdentNr() == nr) {
            index = i;
            break;
        }
    }
    return index;
}
