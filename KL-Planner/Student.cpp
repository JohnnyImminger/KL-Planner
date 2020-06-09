//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Student.h"

/*
 * Konstruktoren
 */

Student::Student() {
    this->matrikelNr = 404;
    this->studiengang = "DummyStudent";
    this->anzKlausuren = 0;
}

Student::Student(int matikelNr, string studiengang) {
    this->matrikelNr = matikelNr;
    this->studiengang = studiengang;
    this->anzKlausuren = 0;
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Student &student) {
    out << student.matrikelNr << ';' << student.studiengang;
    return out;
}

/*
 * Getter
 */

int Student::getMatrikelNr() const {
    return matrikelNr;
}

const string &Student::getStudiengang() const {
    return studiengang;
}

int Student::getAnzKlausuren() const {
    return anzKlausuren;
}

const vector<int> &Student::getKlausurIndizes() const {
    return klausurIndizes;
}

int Student::getIndex() const{
    return index;
}
/*
 * Setter
 */

void Student::setIndex(int index) {
    this->index = index;
}

/*______________________________________________________________
 * Methoden:
 */

void Student::addKlausur(int klausurIndex) {
    anzKlausuren++;
    klausurIndizes.push_back(klausurIndex);
}
