//
// Created by Johnny on 08.06.2020.
//

#include "Student.h"

Student::Student() {
    this->matrikelNr = 404;
    this->studiengang = "DummyStudent";
}



Student::Student(int matikelNr, string studiengang) {
    this->matrikelNr = matikelNr;
    this->studiengang = studiengang;
}



std::ostream &operator<<(ostream &out, const Student &student) {
    out << student.matrikelNr << ';' << student.studiengang;
    return out;
}

int Student::getMatrikelNr() const {
    return matrikelNr;
}

const string &Student::getStudiengang() const {
    return studiengang;
}

void Student::addKlausur(int klausurIndex) {
    anzKlausuren++;
    klausurIndizes.push_back(klausurIndex);
}

/*
void Student::addPruefung(Anmeldung &anmeldung, vector<Klausur> &pruefungenListe) {
    for (int i=0; i<pruefungenListe.size(); i++){
        Klausur pruefung = pruefungenListe [i];
        //TODO muss pNummer und pVersion identisch sein?
        if (pruefung.getPNummer() == anmeldung.getPNummer() && pruefung.getPVersion() == anmeldung.getPVersion()){
            this->pruefungsIndex.push_back(i);
            break;
        }
    }
}
 */
