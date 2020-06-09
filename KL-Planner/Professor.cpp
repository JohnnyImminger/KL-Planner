//
// Created by Johnny on 08.06.2020.
//

#include "Professor.h"

Professor::Professor() {
    this->identNr = 404;
    this->name = "DummyProfessor";
    this->anzPruefungen = 0;
}

Professor::Professor(int identNr, string &name) {
    this->identNr = identNr;
    this->name = name;
    this->anzPruefungen = 0;
}

void Professor::addPruefung(int pIndex) {
    pAufsichtIndex.push_back(pIndex);
    this->anzPruefungen++;
}

std::ostream &operator<<(ostream &out, const Professor &professor) {
    out << professor.identNr << ';' << professor.name << ';' << professor.anzPruefungen;
    return out;
}

int Professor::getIdentNr() const {
    return identNr;
}

const string &Professor::getName() const {
    return name;
}

int Professor::getAnzPruefungen() const {
    return anzPruefungen;
}

vector<Professor> Professor::createProfs() {
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

int Professor::isProfInVector(vector<Professor> &profs, int nr) {
    int index = -1;
    for (int i = 0; i < profs.size(); ++i) {
        if(profs.at(i).getIdentNr() == nr) {
            index = i;
            break;
        }
    }
    return index;
}
