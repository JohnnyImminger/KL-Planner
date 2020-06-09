//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "ReadInput.h"

void ReadInput::init() {
    parseInput();
    createProfs();
    createStudenten();
    attachStudentsToKlausur();
}

void ReadInput::parseInput() {
    this->raeume = Raum::parse("../../input/Raumliste.csv");
    this->anmeldungen = Anmeldung::parse("../../input/Anmeldungen_WS2019_KL.csv");
    this->klausuren = Klausur::parse("../../input/Angebotene_Pruefungen_KL.csv");
}

void ReadInput::createProfs() {
    cout << "creating profs" << endl;
    for (Klausur& klausur: klausuren) {
        if (klausur.getPPruefer1() != 0) {
            int index = isProfInVector(klausur.getPPruefer1());
            if (index >= 0) {
                professoren.at(index).addPruefung(klausur.getIndex());
            } else {
                Professor p(klausur.getPPruefer1(), klausur.getPruefer1());
                p.addPruefung(klausur.getIndex());
                professoren.push_back(p);
            }
        }
        if (klausur.getPPruefer2() != 0) {
            int index = isProfInVector(klausur.getPPruefer2());
            if (index >= 0) {
                professoren.at(index).addPruefung(klausur.getIndex());
            } else {
                Professor p(klausur.getPPruefer2(), klausur.getPruefer2());
                p.addPruefung(klausur.getIndex());
                professoren.push_back(p);
            }
        }
    }
    cout << "done creating profs - " << professoren.size() << " Profs created" << endl;
}

int ReadInput::isProfInVector(int identNr) {
    int index = -1;
    for (int i = 0; i < professoren.size(); ++i) {
        if(professoren.at(i).getIdentNr() == identNr) {
            index = i;
            break;
        }
    }
    return index;
}

void ReadInput::createStudenten() {
    cout << "creating studenten" << endl;
    for (Anmeldung& anmeldung: anmeldungen) {
        int index = isStudentInVector(anmeldung.getMatrikelNr());
        if (index >= 0) {
            studenten.at(index).addKlausur(findKlausurIndex(anmeldung.getPNummer(), anmeldung.getPVersion()));
        } else {
            Student s = Student(s.getMatrikelNr(), s.getStudiengang());
            s.addKlausur(findKlausurIndex(anmeldung.getPNummer(), anmeldung.getPVersion()));
            studenten.push_back(s);
        }
    }
    cout << "done creating studenten - " << professoren.size() << " Studenten created" << endl;
}

int ReadInput::isStudentInVector(int matrikelNr) {
    int index = -1;
    for (int i = 0; i < studenten.size(); ++i) {
        if(studenten.at(i).getMatrikelNr() == matrikelNr) {
            index = i;
            break;
        }
    }
    return index;
}

int ReadInput::findKlausurIndex(int pNummer, int pVersion) {
    for (Klausur& klausur: klausuren) {
        if (klausur.getPNummer() == pNummer && klausur.getPVersion() == pVersion){
            return klausur.getIndex();
        }
    }
    return -1;
}

void ReadInput::attachStudentsToKlausur() {
    cout << "Start Studenten zu Klausuren hinzufuegen" << endl;
    for (const Student& student: studenten) {
        for (int klausurIndex: student.getKlausurIndizes()) {
            klausuren.at(klausurIndex).addStudent(student.getIndex());
        }
    }
    cout << "Studenten zu Klausuren hinzugefuegt" << endl;
}



