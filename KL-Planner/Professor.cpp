//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Professor.h"

/*
 * Konstruktoren
 */

Professor::Professor() {
    this->identNr = 404;
    this->name = "DummyProfessor";
    this->anzPruefungen = 0;
}

Professor::Professor(int identNr, string name) {
    this->identNr = identNr;
    this->name = name;
    this->anzPruefungen = 0;
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Professor &professor) {
    out << professor.identNr << ';' << professor.name << ';' << professor.anzPruefungen;
    return out;
}

/*
 * Getter
 */

int Professor::getIdentNr() const {
    return identNr;
}

const string &Professor::getName() const {
    return name;
}

int Professor::getAnzPruefungen() const {
    return anzPruefungen;
}

const vector<int> &Professor::getKlausurAufsichtIndex() const {
    return klausurAufsichtIndex;
}
/*______________________________________________________________
 * Methoden:
 */

void Professor::addPruefung(int pIndex) {
    klausurAufsichtIndex.push_back(pIndex);
    this->anzPruefungen++;
}


