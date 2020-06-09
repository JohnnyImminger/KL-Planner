//
// Created by Johnny on 08.06.2020.
//

#include "ReadInput.h"

void ReadInput::init() {
    parseInput();
    createProfs();
}

void ReadInput::parseInput() {
    raeume = Raum::parseRaumliste("../../input/Raumliste.csv");
    anmeldungen = Anmeldung::parse("../../input/Anmeldungen_WS2019_KL.csv");
    klausuren = Klausur::parse("../../input/Angebotene_Pruefungen_KL.csv");
}

vector<Professor> ReadInput::createProfs() {
    cout << "creating profs" << endl;
    vector<Professor> profs;
    for (Klausur klausur: klausuren) {
        if (klausur.getPPruefer1() != 0) {
            int index = isProfInVector(profs, klausur.getPPruefer1());
            if (index >= 0) {
                profs.at(index).addPruefung(klausur.getIndex());
            } else {
                Professor p(klausur.getPPruefer1(), klausur.getPruefer1());
                p.addPruefung(klausur.getIndex());
                profs.push_back(p);
            }
        }
        if (klausur.getPPruefer2() != 0) {
            int index = isProfInVector(profs, klausur.getPPruefer2());
            if (index >= 0) {
                profs.at(index).addPruefung(klausur.getIndex());
            } else {
                Professor p(klausur.getPPruefer2(), klausur.getPruefer2());
                p.addPruefung(klausur.getIndex());
                profs.push_back(p);
            }
        }
    }
    cout << "done creating profs - " << profs.size() << " Profs created" << endl;
    return profs;
}

int ReadInput::isProfInVector(vector<Professor> &profs, int nr) {
    int index = -1;
    for (int i = 0; i < profs.size(); ++i) {
        if(profs.at(i).getIdentNr() == nr) {
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
