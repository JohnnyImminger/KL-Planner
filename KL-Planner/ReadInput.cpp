//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "ReadInput.h"

#include <utility>

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
    for (Klausur& klausur: klausuren) {
        if (klausur.getPPruefer1() != 0) {
            processProf(klausur.getIndex(), klausur.getPPruefer1(), klausur.getPruefer1());
        }
        if (klausur.getPPruefer2() != 0) {
            processProf(klausur.getIndex(), klausur.getPPruefer2(), klausur.getPruefer2());
        }
    }
    cout << professoren.size() << " Professoren angelegt" << endl;
}
void ReadInput::processProf(int klausurIndex, int id, const string &name) {
    int index = isProfInVector(id);
    if (index >= 0) {
        professoren.at(index).addPruefung(klausurIndex);
    } else {
        Professor p(id, name);
        p.addPruefung(klausurIndex);
        professoren.push_back(p);
    }
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
    int countMissingSignings = 0;
    int studentenCount = 0;
    for (Anmeldung& anmeldung: anmeldungen) {
        int index = isStudentInVector(anmeldung.getMatrikelNr());
        int klausurIndex = findKlausurIndex(anmeldung.getPNummer(), anmeldung.getPVersion());
        if (klausurIndex < 0){
            //cout << anmeldung << endl;
            //cout << "Klausur konnte nicht gefunden werden!" << endl;
            countMissingSignings++;
            continue;
        }
        if (index >= 0) {
            studenten.at(index).addKlausur(klausurIndex);
        } else {
            Student s = Student(anmeldung.getMatrikelNr(), anmeldung.getStudiengang());
            s.addKlausur(klausurIndex);
            s.setIndex(studentenCount);
            studenten.push_back(s);
            studentenCount++;
        }
    }
    cout << "Klausur für Anmeldung nicht gefunden: " << countMissingSignings << endl;
    cout << studenten.size() << " Studenten angelegt" << endl;
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
        //TODO is pVersion important?
        if (klausur.getPNummer() == pNummer){ //&& klausur.getPVersion() == pVersion
            return klausur.getIndex();
        }
    }
    return -1;
}

void ReadInput::attachStudentsToKlausur() {
    for (const Student& student: studenten) {
        for (int klausurIndex: student.getKlausurIndizes()) {
            klausuren.at(klausurIndex).addStudent(student.getIndex());
        }
    }
    cout << "Studenten zu Klausuren hinzugefuegt" << endl;
}