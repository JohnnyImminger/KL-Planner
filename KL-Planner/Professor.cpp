//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Professor.h"

/*
 * Konstruktoren
 */

Professor::Professor() {
    this->index = -1;
    this->identNr = 404;
    this->name = "DummyProfessor";
    this->examCount = 0;
}

Professor::Professor(int identNr, string name) {
    this->index = -1;
    this->identNr = identNr;
    this->name = name;
    this->examCount = 0;
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Professor &professor) {
    out << professor.getIdentNr() << ';' << professor.getName() << ';' << professor.getExamCount();
    return out;
}

/*
 * Getter
 */

int Professor::getIndex() const {
    return index;
}

int Professor::getIdentNr() const {
    return identNr;
}

const string &Professor::getName() const {
    return name;
}

int Professor::getExamCount() const {
    return examCount;
}

const vector<int> &Professor::getExamIndices() const {
    return examIndices;
}

/*
 * Setter
 */

void Professor::setIndex(int index) {
    this->index = index;
}


/*______________________________________________________________
 * Methoden:
 */

void Professor::addKlausur(int examIndex) {
    this->examIndices.push_back(examIndex);
    this->examCount++;
}
