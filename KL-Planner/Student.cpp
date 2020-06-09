//
// Created by Johnny on 08.06.2020.
//

#include "Student.h"

Student::Student() {
    this->matrikelNr = 404;
    this->studiengang = "DummyStudent";
    this->anzPruefungen = 0;
}



Student::Student(int matikelNr, string& studiengang) {
    this->matrikelNr = matikelNr;
    this->studiengang = studiengang;
    this->anzPruefungen = 0;
}

void Student::addPruefung() {
    this->anzPruefungen++;
}

std::ostream &operator<<(ostream &out, const Student &student) {
    out << student.matrikelNr << ';' << student.studiengang << ';' << student.anzPruefungen;
    return out;
}
