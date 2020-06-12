//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Professor.h"

/*
 * Konstruktoren
 */

Professor::Professor() {
    this->dataIndex = -1;
    this->identNr = 404;
    this->name = "DummyProfessor";
    this->anzKlausuren = 0;
}

Professor::Professor(int identNr, string& name) {
    this->dataIndex = -1;
    this->identNr = identNr;
    this->name = name;
    this->anzKlausuren = 0;
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Professor &professor) {
    out << professor.getIdentNr() << ';' << professor.getName() << ';' << professor.getAnzKlausuren();
    return out;
}

/*
 * Getter
 */

int Professor::getDataIndex() const {
    return dataIndex;
}

int Professor::getIdentNr() const {
    return identNr;
}

const string &Professor::getName() const {
    return name;
}

int Professor::getAnzKlausuren() const {
    return anzKlausuren;
}

const vector<int> &Professor::getKlausurDataIndizes() const {
    return klausurDataIndizes;
}

/*
 * Setter
 */

void Professor::setIndex(int index) {
    this->dataIndex = index;
}


/*______________________________________________________________
 * Methoden:
 */

void Professor::addKlausur(int klausurDataIndex) {
    this->klausurDataIndizes.push_back(klausurDataIndex);
    this->anzKlausuren++;
}
