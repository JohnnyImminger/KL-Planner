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

void Professor::addPruefung() {
    this->anzPruefungen++;
}

std::ostream &operator<<(ostream &out, const Professor &professor) {
    out << professor.identNr << ';' << professor.name << ';' << professor.anzPruefungen;
    return out;
}