//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "Student.h"

/*
 * Konstruktoren
 */

Student::Student() {
    this->dataIndex = -1;
    this->matrikelNr = 404;
    this->studiengang = "DummyStudent";
    this->amountExams = 0;
}

Student::Student(int matikelNr, string studiengang) {
    this->dataIndex = -1;
    this->matrikelNr = matikelNr;
    this->studiengang = studiengang;
    this->amountExams = 0;
}

/*
 * toString()
 */

std::ostream &operator<<(ostream &out, const Student &student) {
    out << student.getMatrikelNr() << ';' << student.getStudiengang() << ';' << student.getAmountExams();
    return out;
}

/*
 * Getter
 */

int Student::getDataIndex() const{
    return dataIndex;
}

int Student::getMatrikelNr() const {
    return matrikelNr;
}

const string &Student::getStudiengang() const {
    return studiengang;
}

int Student::getAmountExams() const {
    return amountExams;
}

const vector<int> &Student::getExamDataIndizes() const {
    return examDataIndizes;
}

/*
 * Setter
 */

void Student::setIndex(int index) {
    this->dataIndex = index;
}

/*______________________________________________________________
 * Methoden:
 */

void Student::addKlausur(int klausurDataIndex) {
    this->examDataIndizes.push_back(klausurDataIndex);
    this->amountExams++;
}
