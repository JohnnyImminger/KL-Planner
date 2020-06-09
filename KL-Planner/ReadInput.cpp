//
// Created by Johnny Imminger, Felix Steinke and Florian Grabowski
//

#include "ReadInput.h"

void ReadInput::init() {
    parseInput();
    createProfs();
    attachStudentsToKlausur();
}

void ReadInput::parseInput() {
    this->raeume = Raum::parse("../../input/Raumliste.csv");
    this->anmeldungen = Anmeldung::parse("../../input/Anmeldungen_WS2019_KL.csv");
    this->klausuren = Klausur::parse("../../input/Angebotene_Pruefungen_KL.csv");
}

void ReadInput::createProfs() {
    cout << "creating profs" << endl;
    for (Klausur klausur: klausuren) {
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

int ReadInput::isProfInVector(int nr) {
    int index = -1;
    for (int i = 0; i < professoren.size(); ++i) {
        if(professoren.at(i).getIdentNr() == nr) {
            index = i;
            break;
        }
    }
    return index;
}



vector<Student> ReadInput::initStudenten(vector<Anmeldung> &anmeldungenListe, vector<Klausur> &pruefungenListe) {
    int counter = 0;
    vector<Student> liste;
    //TODO
    /*
    for (auto& anmeldung : anmeldungenListe){
        for (auto& studenten : liste){
            if (studenten.getMatrikelNr() == anmeldung.getMatrikelNr()){
                studenten.addPruefung(anmeldung, pruefungenListe);
                break;
            }
            Student st = Student(anmeldung.getMatrikelNr(),anmeldung.getStudiengang());
            st.addPruefung(anmeldung, pruefungenListe);
            liste.push_back(Student(anmeldung.getMatrikelNr(),anmeldung.getStudiengang()));
            counter++;
        }
    }
     */
    cout << counter << " Studenten wurden erzeugt."  << endl;
    return liste;
}

void ReadInput::attachStudentsToKlausur() {
    cout << "Start Studenten zu Klausuren hinzufügen" << endl;
    for (const Student& student: studenten) {
        for (int klausurIndex: student.getKlausurIndizes()) {
            klausuren.at(klausurIndex).addStudent(student.getIndex());
        }
    }
    cout << "Studenten zu Klausuren hinzugefügt" << endl;
}



/*
 * void Student::addPruefung(Anmeldung &anmeldung, vector<Klausur> &pruefungenListe) {
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
